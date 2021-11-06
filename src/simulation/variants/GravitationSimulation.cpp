#include <spdlog/spdlog.h>
#include "GravitationSimulation.h"

void GravitationSimulation::performSimulation(Argument &arg, OutputWriter &writer,
                                              ParticleContainer &particleContainer) {
  Gravitation gravitation;
  Simulation::performSimulation(writer, gravitation, particleContainer, arg);
  SPDLOG_INFO("Output written, terminating");
}
