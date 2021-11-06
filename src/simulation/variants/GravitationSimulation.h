#pragma once

#include <simulation/Simulation.h>

/**
 * Subclass of the Simulation class which performs the Simulation.
 */
class GravitationSimulation : public Simulation {
 public:

  /**
   * Performs the simulation via a default Gravitation.
   * @param arg Argument given by the main-Method.
   * @param writer Defines the writer for the output.
   * @param particleContainer
   */
  static void performSimulation(const Argument &arg, OutputWriter &writer, ParticleContainer &particleContainer);
};
