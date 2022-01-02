#pragma once

#include <iostream>
#include <type_traits>

#include "logger/Logger.h"
#include "outputWriter/VTKWriter/VTKWriter.h"
#include "arguments/argument/Argument.h"
#include "arguments/argumentParser/BasicArgumentParser/BasicArgumentParser.h"
#include "physics/Physics.h"
#include "physics/LinkedCell/LinkedCellParallelLockFree.h"

/**
 * Simulation class which contains a start time and a method to run a simulation.
 * @tparam T type of physics used in this simulation.
 * @tparam dim dimension of our simulation.
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
   * @param writer Defines the writer for the output.
   * @param physics The Physics to be used.
   * @param particleContainer The initial particles.
   * @param arg The command line-arguments.
   */
  static void performSimulation([[maybe_unused]] OutputWriter<dim> &writer, ParticleContainer<dim> &particleContainer,
                                Argument<dim> &arg) {
    double current_time = start_time;
    int iteration = 0;
    auto deltaT = arg.getDeltaT();

    T physics;

    if constexpr(std::is_same<T, LinkedCellParallelLockFree<LennardJones,dim>>::value) {
      // TODO Fix cast with check
      auto &xmlArg = static_cast<XMLArgument<dim> &>(arg);
      physics = T(xmlArg.getCutoffRadius().value(), xmlArg.getCellSize().value(), particleContainer);
    }

    std::unique_ptr<Thermostat<dim>>& thermostat = arg.getThermostat();

    thermostat->setInitialTemperature(particleContainer);

    double additionalForce = arg.getAdditionalGravitation();

    // for this loop, we assume: current x, current f and current v are known
    while (current_time < arg.getEndTime()) {
      physics.calculateNextStep(particleContainer, deltaT, additionalForce);

      if (iteration % thermostat->getNumberT() == 0) {
        thermostat->applyThermostat(particleContainer);
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
  };
};
