#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO

#include "spdlog/spdlog.h"
#include "GravitationSimulation.h"

void GravitationSimulation::performSimulation(const Argument &arg, OutputWriter &writer,
                                              ParticleContainer &particleContainer) {
  Gravitation gravitation;
  Simulation::performSimulation(writer, gravitation, particleContainer, arg);
  SPDLOG_INFO("Output written, terminating");
}
