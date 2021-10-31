//
// Created by domi on 31/10/2021.
//

#include "GravitationSimulation.h"

void GravitationSimulation::performSimulation(Argument &arg, OutputWriter &writer,
                                                         ParticleContainer &particleContainer) {
  Gravitation gravitation;
  Simulation::performSimulation(writer, gravitation, particleContainer, arg);
  std::cout << "output written. Terminating..." << std::endl;
}
