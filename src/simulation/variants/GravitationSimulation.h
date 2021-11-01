#pragma once

#include <simulation/Simulation.h>

class GravitationSimulation : public Simulation {
 public:
  static void performSimulation(Argument &arg, OutputWriter &writer, ParticleContainer &particleContainer);
};
