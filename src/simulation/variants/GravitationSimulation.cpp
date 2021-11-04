#include "GravitationSimulation.h"

void GravitationSimulation::performSimulation(Argument &arg, OutputWriter &writer,
                                              ParticleContainer &particleContainer) {
  Gravitation gravitation;
  Simulation::performSimulation(writer, gravitation, particleContainer, arg);
  std::cout << "output written. Terminating..." << std::endl;
}
