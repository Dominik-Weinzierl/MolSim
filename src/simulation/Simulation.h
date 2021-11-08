#pragma once

#include "outputWriter/VTKWriter/VTKWriter.h"
#include <iostream>
#include <physics/Gravitation/Gravitation.h>
#include <arguments/argument/Argument.h>
#include <arguments/argumentParser/BasicArgumentParser/BasicArgumentParser.h>

/**
 * Simulation class which contains a start time and a method to run a simulation.
 */
class Simulation {
 protected:
  static constexpr double start_time = 0;

  /**
   * Performs the simulation via a default Gravitation.
   * @param writer Defines the writer for the output.
   * @param physics The Physics to be used.
   * @param particleContainer The initial particles.
   * @param arg The command line-arguments.
   */
  static void performSimulation(OutputWriter &writer, const Physics &physics, ParticleContainer &particleContainer,
                                const Argument &arg);
};
