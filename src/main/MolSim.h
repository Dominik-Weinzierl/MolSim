#pragma once

#include <iostream>
#include <iomanip>
#include <omp.h>

#include "logger/Logger.h"
#include "arguments/argument/Argument.h"
#include "outputWriter/XYZWriter/XYZWriter.h"
#include "arguments/argumentParser/ParserStrategy.h"
#include "fileReader/InputFile/InputReader.h"
#include "outputWriter/DummyWriter/DummyWriter.h"
#include "physics/variants/Gravitation.h"
#include "simulation/MDSimulation.h"
#include "physics/DirectSum.h"
#include "physics/LinkedCell/LinkedCell.h"
#include "container/DirectSum/DirectSumContainer.h"
#include "container/LinkedCell/LinkedCellContainer.h"
#include "container/ParticleContainer.h"
#include "fileReader/VTKReader/VTKReader.h"
#include "physics/LinkedCell/LinkedCellParallelLockFree.h"
#include "physics/LinkedCell/LinkedCellParallelBuffer.h"
#include "physics/LinkedCell/LinkedCellParallelCellLock.h"
#include "physics/LinkedCell/LinkedCellParallelOptimizedLock.h"

/**
 * Provides static functions for simulation and benchmark.
 * @tparam dim dimension of our simulation
 */
template<size_t dim>
class MolSim {
  /**
   * Arguments used by our simulation.
   */
  std::unique_ptr<Argument<dim>> arg;

  /**
   * Writer used for our simulation.
   */
  std::unique_ptr<OutputWriter<dim>> writer;

  /**
   * ParticleContainer used by our simulation.
   */
  std::unique_ptr<ParticleContainer<dim>> particleContainer;

 public:

  //----------------------------------------Methods----------------------------------------

  /**
   * Setup project based on selected dimension.
   * @param args input arguments
   * @return successful setup
   */
  int setup(const std::vector<std::string> &args) {
    // Init strategy and select correct parser.
    ParserStrategy<dim> strategy = ParserStrategy<dim>{args};

    // If there is no need to parse, we can end here.
    if (args.empty() || (std::string{args[0]} == "-h" || std::string{args[0]} == "--help")) {
      ParserStrategy<dim>::showUsage();
      return 0;
    }

    // Setup logger if required.
    Logger::setupLogger();

    // Set the parser.
    std::unique_ptr<ArgumentParser<dim>> parser = strategy.getParser();

    // Validate input.
    try {
      parser->validateInput();
    } catch (std::invalid_argument &exception) {
      std::cout << "[ERROR] " << exception.what() << std::endl;
      SPDLOG_ERROR(exception.what());
      ParserStrategy<dim>::showUsage();
      return -1;
    }

    // Collect arguments parsed by Parser.
    try {
      arg = parser->createArgument();
    } catch (std::invalid_argument &exception) {
      std::cout << "[ERROR] " << exception.what() << "! Please check your input file." << std::endl;
      SPDLOG_ERROR(exception.what());
      return -1;
    }

    // Setup container.
    if (arg->getStrategy() == "DirectSum") {
      particleContainer = std::make_unique<DirectSumContainer<dim>>();
    } else {
      auto &xmlArg = static_cast<XMLArgument<dim> &>(*arg);
      particleContainer =
          std::make_unique<LinkedCellContainer<dim>>(xmlArg.getBoundaries().value(), xmlArg.getCellSize().value(),
                                                     xmlArg.getDomain().value(), xmlArg.getCutoffRadius().value());
      particleContainer->init();
    }

    // Select Writer.
    if (arg->getWriter() == "vtk") {
      writer = std::make_unique<VTKWriter<dim>>(arg->getOutput(), "output", *particleContainer);
    } else if (arg->getWriter() == "xyz") {
      writer = std::make_unique<XYZWriter<dim>>(arg->getOutput(), "output", *particleContainer);
    }

    // Read additional files.
    for (std::string &file: arg->getFiles()) {
      std::string fileEnding = file.substr(file.size() - 3);
      if (fileEnding == "txt") {
        InputReader<dim>::readFile(*particleContainer, file);
      } else if (fileEnding == "vtu") {
        VTKReader<dim>::readFromFile(*particleContainer, file);
      } else {
        std::cout << "Unaccepted file format" << std::endl;
        return -1;
      }
    }

    // Create Particles (with Generators)
    arg->createAdditionalParticle(*particleContainer);

    std::cout << "Configuration loaded..." << std::endl;
    std::cout << "Selected dimension: " << dim << "D..." << std::endl;
    std::cout << arg->toString() << std::endl;

    return 1;
  }

  /**
   * Simulation of our Particle(s).
   * @return 0
   */
  int simulate() {
    long int duration = 0;
    if (arg->getPhysics() == "gravitation") {
      if (arg->getStrategy() == "DirectSum") {
        duration = MDSimulation<DirectSum<Gravitation, dim>, dim>::performSimulation(*writer, *particleContainer, *arg);
      }
    } else if (arg->getPhysics() == "lennard") {
      if (arg->getStrategy() == "LinkedCell") {
        auto &xmlArg = static_cast<XMLArgument<dim> &>(*arg);
        if (xmlArg.getParallel() == "lock-free") {
          duration = MDSimulation<LinkedCellParallelLockFree<LennardJones, dim>, dim>::performSimulation(*writer,
                                                                                                         *particleContainer,
                                                                                                         *arg);
        } else if (xmlArg.getParallel() == "buffer") {
          duration = MDSimulation<LinkedCellParallelBuffer<LennardJones, dim>, dim>::performSimulation(*writer,
                                                                                                       *particleContainer,
                                                                                                       *arg);
        } else if (xmlArg.getParallel() == "lock-cell") {
          duration = MDSimulation<LinkedCellParallelCellLock<LennardJones, dim>, dim>::performSimulation(*writer,
                                                                                                         *particleContainer,
                                                                                                         *arg);
        } else if (xmlArg.getParallel() == "lock-optimized") {
          duration = MDSimulation<LinkedCellParallelOptimizedLock<LennardJones, dim>, dim>::performSimulation(*writer,
                                                                                                              *particleContainer,
                                                                                                              *arg);
        } else {
          duration =
              MDSimulation<LinkedCell<LennardJones, dim>, dim>::performSimulation(*writer, *particleContainer, *arg);
        }
      } else {
        duration =
            MDSimulation<DirectSum<LennardJones, dim>, dim>::performSimulation(*writer, *particleContainer, *arg);
      }
    }
    std::cout << "Finished simulation after " << arg->getEndTime() / arg->getDeltaT() << " iterations..." << std::endl;
    std::cout << "Output written..." << std::endl;
    std::cout << "Time: " << duration << " ms" << std::endl;
#ifdef _OPENMP
    std::cout << "Threads: " << omp_get_max_threads() << std::endl;
#endif
    return 0;
  };

  /**
   * Benchmarking of our simulation (with DummyWriter).
   * @return 0
   */
  int benchmark() {
    auto benchWriter = std::make_unique<DummyWriter<dim>>(arg->getOutput(), *particleContainer);
    // Replace with dummy
    arg->getProfileWriter() = std::make_unique<DummyProfileWriter<dim>>();
    auto particleAmount = particleContainer->size();
    long int duration = 0;
    if (arg->getPhysics() == "gravitation") {
      if (arg->getStrategy() == "DirectSum") {
        duration =
            MDSimulation<DirectSum<Gravitation, dim>, dim>::performSimulation(*benchWriter, *particleContainer, *arg);
      }
    } else if (arg->getPhysics() == "lennard") {
      if (arg->getStrategy() == "LinkedCell") {
        auto &xmlArg = static_cast<XMLArgument<dim> &>(*arg);
        if (xmlArg.getParallel() == "lock-free") {
          duration = MDSimulation<LinkedCellParallelLockFree<LennardJones, dim>, dim>::performSimulation(*benchWriter,
                                                                                                         *particleContainer,
                                                                                                         *arg);
        } else if (xmlArg.getParallel() == "buffer") {
          duration = MDSimulation<LinkedCellParallelBuffer<LennardJones, dim>, dim>::performSimulation(*benchWriter,
                                                                                                       *particleContainer,
                                                                                                       *arg);
        } else if (xmlArg.getParallel() == "lock-cell") {
          duration = MDSimulation<LinkedCellParallelCellLock<LennardJones, dim>, dim>::performSimulation(*benchWriter,
                                                                                                         *particleContainer,
                                                                                                         *arg);
        } else if (xmlArg.getParallel() == "lock-optimized") {
          duration =
              MDSimulation<LinkedCellParallelOptimizedLock<LennardJones, dim>, dim>::performSimulation(*benchWriter,
                                                                                                       *particleContainer,
                                                                                                       *arg);
        } else {
          duration =
              MDSimulation<LinkedCell<LennardJones, dim>, dim>::performSimulation(*benchWriter, *particleContainer,
                                                                                  *arg);
        }
      } else {
        duration =
            MDSimulation<DirectSum<LennardJones, dim>, dim>::performSimulation(*benchWriter, *particleContainer, *arg);
      }
    }
    auto iterations = std::floor(arg->getEndTime() / arg->getDeltaT());
    std::cout << "Finished benchmarks after " << iterations << " iterations..." << std::endl;
    std::cout << std::endl;
    std::cout << "Details:" << std::endl;
    std::cout << "\t\tTime: " << duration << " ms" << std::endl;
    std::cout << "\t\tParticle amount - start: " << particleAmount << " particle" << std::endl;
    std::cout << "\t\tParticle amount - end: " << particleContainer->size() << " particle" << std::endl;
    std::cout << "\t\tIterations: " << iterations << std::endl;
    std::cout << "\t\tMMUPS/s: "
              << ((iterations * static_cast<double>(particleAmount)) / static_cast<double>(duration)) / 1.0e3
              << std::endl;
#ifdef _OPENMP
    std::cout << "\t\tThreads: " << omp_get_max_threads() << std::endl;
#endif
    return 0;
  };

  /**
   * Select benchmark or simulation.
   * @param args input arguments
   * @return 0
   */
  int selectMethod(const std::vector<std::string> &args) {
    if (std::find(args.begin(), args.end(), "-b") != args.end()
        || std::find(args.begin(), args.end(), "--benchmark") != args.end()) {
      std::cout << "Perform benchmarks..." << std::endl;
      return MolSim<dim>::benchmark();
    } else {
      std::cout << "Perform simulation... " << std::endl;
      return MolSim<dim>::simulate();
    }
  };

  /**
   * Wrapper to minimize code duplicate in main.
   * @param args arguments
   * @return status of selected operation
   */
  static int run(const std::vector<std::string> &args) {
    MolSim<dim> sim{};

    int value = sim.setup(args);
    if (value != 1)
      return value;
    return sim.selectMethod(args);
  };

  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * Getter for argument.
   * @return std::unique_ptr<Argument<dim>> & arg
   */
  const std::unique_ptr<Argument<dim>> &getArg() const {
    return arg;
  }

  /**
   * Getter for writer.
   * @return std::unique_ptr<OutputWriter<dim>> & writer
   */
  const std::unique_ptr<OutputWriter<dim>> &getWriter() const {
    return writer;
  }

  /**
   * Getter for particleContainer.
   * @return std::unique_ptr<ParticleContainer<dim>> & particleContainer
   */
  const std::unique_ptr<ParticleContainer<dim>> &getParticleContainer() const {
    return particleContainer;
  }
};
