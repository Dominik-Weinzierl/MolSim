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

/**
 * Provides static functions for simulation and benchmark.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class MolSim {
 public:
  /**
   * Simulation of our Particle(s).
   * @param arg arguments used during our simulation
   * @param writer selected writer
   * @param particleContainer particle(s)
   * @return
   */
  static int simulate(std::unique_ptr<Argument<dim>> &arg, std::unique_ptr<OutputWriter<dim>> &writer,
                      ParticleContainer<dim> &particleContainer) {
    if (arg->getPhysics() == "gravitation") {
      MDSimulation<Gravitation<dim>, dim>::performSimulation(*writer, particleContainer, *arg);
    } else if (arg->getPhysics() == "lennard") {
      MDSimulation<LennardJones<dim>, dim>::performSimulation(*writer, particleContainer, *arg);
    }
    std::cout << "Finished simulation after " << arg->getEndTime() / arg->getDeltaT() << " iterations..." << std::endl;
    std::cout << "Output written..." << std::endl;
    return 0;
  };

  /**
   * Benchmarking of our simulation (with DummyWriter).
   * @param arg arguments used during our simulation
   * @param particleContainer particle(s)
   * @return
   */
  static int benchmark(std::unique_ptr<Argument<dim>> &arg, ParticleContainer<dim> &particleContainer) {
    auto writer = std::make_unique<DummyWriter<dim>>(arg->getOutput(), "benchmark", particleContainer);
    auto start = std::chrono::high_resolution_clock::now();
    if (arg->getPhysics() == "gravitation") {
      MDSimulation<Gravitation<dim>, dim>::performSimulation(*writer, particleContainer, *arg);
    } else if (arg->getPhysics() == "lennard") {
      MDSimulation<LennardJones<dim>, dim>::performSimulation(*writer, particleContainer, *arg);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Finished benchmarks after " << arg->getEndTime() / arg->getDeltaT() << " iterations..." << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms"
              << std::endl;
    return 0;
  };
};