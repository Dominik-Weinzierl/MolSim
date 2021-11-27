#pragma once

#include "logger/Logger.h"

#include <arguments/argument/Argument.h>
#include <iostream>
#include <outputWriter/XYZWriter/XYZWriter.h>
#include <arguments/argumentParser/ParserStrategy.h>
#include "fileReader/InputFile/InputReader.h"
#include <iomanip>
#include <outputWriter/DummyWriter/DummyWriter.h>
#include "simulation/MDSimulation.h"
#include "physics/LennardJones/LennardJones.h"
#include "container/DirectSumContainer.h"

/**
 * Provides static functions for simulation and benchmark.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class MolSim {
 private:
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
  DirectSumContainer<dim> particleContainer;

  /**
   * Setup project based on selected dimension.
   * @param args input arguments
   * @return successful setup
   */
  int setup(const std::vector<std::string> &args) {
    ParserStrategy<dim> strategy = ParserStrategy<dim>{args};

    if (args.empty() || (std::string{args[0]} == "-h" || std::string{args[0]} == "--help")) {
      ParserStrategy<dim>::showUsage();
      return 0;
    }

    Logger::setupLogger();

    std::unique_ptr<ArgumentParser<dim>> parser = strategy.getParser();

    try {
      parser->validateInput();
    } catch (std::invalid_argument &exception) {
      std::cout << "[ERROR] " << exception.what() << std::endl;
      SPDLOG_ERROR(exception.what());
      ParserStrategy<dim>::showUsage();
      return -1;
    }

    try {
      arg = parser->createArgument();
    } catch (std::invalid_argument &exception) {
      std::cout << "[ERROR] " << exception.what() << "! Please check your input file." << std::endl;
      SPDLOG_ERROR(exception.what());
      return -1;
    }

    if (arg->getWriter() == "vtk") {
      writer = std::make_unique<VTKWriter<dim>>(arg->getOutput(), "output", particleContainer);
    } else if (arg->getWriter() == "xyz") {
      writer = std::make_unique<XYZWriter<dim>>(arg->getOutput(), "output", particleContainer);
    }

    for (const auto &file: arg->getFiles()) {
      InputReader<dim>::readFile(particleContainer, file);
    }

    arg->createAdditionalParticle(particleContainer);

    std::cout << "Configuration loaded..." << std::endl;
    std::cout << "Selected dimension: " << dim << "D..." << std::endl;
    std::cout << arg->toString() << std::endl;

    return 1;
  }

  /**
   * Simulation of our Particle(s).
   * @return
   */
  int simulate() {
    auto start = std::chrono::high_resolution_clock::now();
    if (arg->getPhysics() == "gravitation") {
      MDSimulation<Gravitation<dim>, dim>::performSimulation(*writer, particleContainer, *arg);
    } else if (arg->getPhysics() == "lennard") {
      MDSimulation<LennardJones<dim>, dim>::performSimulation(*writer, particleContainer, *arg);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Finished simulation after " << arg->getEndTime() / arg->getDeltaT() << " iterations..." << std::endl;
    std::cout << "Output written..." << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms"
              << std::endl;
    return 0;
  };

  /**
   * Benchmarking of our simulation (with DummyWriter).
   * @return
   */
  int benchmark() {
    auto benchWriter = std::make_unique<DummyWriter<dim>>(arg->getOutput(), particleContainer);
    auto start = std::chrono::high_resolution_clock::now();
    if (arg->getPhysics() == "gravitation") {
      MDSimulation<Gravitation<dim>, dim>::performSimulation(*benchWriter, particleContainer, *arg);
    } else if (arg->getPhysics() == "lennard") {
      MDSimulation<LennardJones<dim>, dim>::performSimulation(*benchWriter, particleContainer, *arg);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Finished benchmarks after " << arg->getEndTime() / arg->getDeltaT() << " iterations..." << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms"
              << std::endl;
    return 0;
  };

  /**
   * Select benchmark or simulation.
   * @param args input arguments
   * @return return 0;
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

 public:
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
};