#pragma once

class LennardSimulation : public Simulation{
 public:

  /**
   * Performs the simulation via a default Lennard Jones potential.
   * @param arg Argument given by the main-Method.
   * @param writer Defines the writer for the output.
   * @param particleContainer
   */
  static void performSimulation(const Argument &arg, OutputWriter &writer, ParticleContainer &particleContainer);
};

