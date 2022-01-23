#pragma once

#include <iostream>
#include <type_traits>

#include "logger/Logger.h"
#include "outputWriter/VTKWriter/VTKWriter.h"
#include "arguments/argument/Argument.h"
#include "arguments/argumentParser/BasicArgumentParser/BasicArgumentParser.h"
#include "physics/Physics.h"
#include "physics/LinkedCell/LinkedCellParallelLockFree.h"
#include "physics/LinkedCell/LinkedCellParallelOptimizedLock.h"

/**
 * Simulation class which contains a start time and a method to run a simulation.
 * @tparam T type of physics used in this simulation
 * @tparam dim dimension of our simulation
 */
template<typename T, size_t dim>
class MDSimulation {
  /**
   * Start time which is zero currently.
   */
  static constexpr double start_time = 0;

 public:

  //----------------------------------------Methods----------------------------------------

  /**
   * Performs the simulation via a default Gravitation.
   * @param writer Defines the writer for the output
   * @param physics The Physics to be used
   * @param particleContainer The initial particles
   * @param arg The command line-arguments
   */
  static auto performSimulation([[maybe_unused]] OutputWriter<dim> &writer, ParticleContainer<dim> &particleContainer,
                                Argument<dim> &arg) {
    double current_time = start_time;
    int iteration = 0;
    auto deltaT = arg.getDeltaT();

    T physics;

    if constexpr(std::is_same<T, LinkedCellParallelLockFree<LennardJones, dim>>::value
        || std::is_same<T, LinkedCellParallelOptimizedLock<LennardJones, dim>>::value) {
      auto &xmlArg = static_cast<XMLArgument<dim> &>(arg);
      physics = T(xmlArg.getCutoffRadius().value(), xmlArg.getCellSize().value(), particleContainer);
    }

    std::unique_ptr<Thermostat<dim>> &thermostat = arg.getThermostat();
    std::unique_ptr<ProfileWriter<dim>> &profile_writer = arg.getProfileWriter();

    thermostat->setInitialTemperature(particleContainer);

    Vector<dim> gravitation = arg.getAdditionalGravitation();

    auto start = std::chrono::high_resolution_clock::now();

    // for this loop, we assume: current x, current f and current v are known
    while (current_time < arg.getEndTime()) {
      physics.calculateNextStep(particleContainer, deltaT, gravitation, current_time);

      if (iteration % thermostat->getNumberT() == 0) {
        thermostat->applyThermostat(particleContainer);
      }

      if (iteration % profile_writer->getNumOfIterations() == 0) {
        profile_writer->generateProfiles(particleContainer, iteration);
      }

      if (iteration % arg.getIteration() == 0) {
        writer.writeFile(iteration);
      }

      if (iteration % 500 == 0) {
        SPDLOG_INFO("Iteration {} finished", iteration);
      } else {
        SPDLOG_TRACE("Iteration {} finished", iteration);
      }

      iteration++;
      current_time += deltaT;
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  };
};
