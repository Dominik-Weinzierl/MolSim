#pragma once

#include "logger/Logger.h"

#include "outputWriter/VTKWriter/VTKWriter.h"
#include <iostream>
#include <physics/Gravitation/Gravitation.h>
#include <arguments/argument/Argument.h>
#include <arguments/argumentParser/BasicArgumentParser/BasicArgumentParser.h>

/**
 * Simulation class which contains a start time and a method to run a simulation.
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<Physics<dim>, T>::value, bool>::type = true>
class MDSimulation {
  static constexpr double start_time = 0;

 public:
  /**
   * Performs the simulation via a default Gravitation.
   * @param writer Defines the writer for the output.
   * @param physics The Physics to be used.
   * @param particleContainer The initial particles.
   * @param arg The command line-arguments.
   */
  static void performSimulation([[maybe_unused]] OutputWriter<dim> &writer, ParticleContainer<dim> &particleContainer,
                                const Argument<dim> &arg) {
    double current_time = start_time;
    int iteration = 0;
    auto deltaT = arg.getDeltaT();

    T physics;

    // for this loop, we assume: current x, current f and current v are known
    while (current_time < arg.getEndTime()) {
      physics.calculateNextStep(particleContainer, deltaT);

      /*if (iteration % arg.getIteration() == 0) {
        writer.writeFile(iteration);
      }*/

      SPDLOG_INFO("Iteration {} finished", iteration);

      iteration++;
      current_time += deltaT;
    }

    SPDLOG_INFO("Output written, terminating");
  };
};

