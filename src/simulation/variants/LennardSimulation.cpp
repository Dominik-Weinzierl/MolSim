#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF

#include <arguments/argument/Argument.h>
#include <simulation/Simulation.h>
#include "LennardSimulation.h"
#include "physics/LennardJones/LennardJones.h"
#include "spdlog/spdlog.h"


void LennardSimulation::performSimulation(const Argument &arg, OutputWriter &writer,
                                          ParticleContainer &particleContainer) {
  LennardJones lennardJones;
  Simulation::performSimulation(writer, lennardJones, particleContainer, arg);
  SPDLOG_INFO("Output written, terminating");
}
