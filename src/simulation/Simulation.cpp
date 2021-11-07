#include <spdlog/spdlog.h>
#include "Simulation.h"

void Simulation::performSimulation(OutputWriter &writer, const Physics &physics, ParticleContainer &particleContainer,
                                   const Argument &arg) {
  double current_time = start_time;
  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < arg.getEndTime()) {
    physics.calculateNextStep(particleContainer, arg.getDeltaT());

    iteration++;

    if (iteration % arg.getIteration() == 0) {
      writer.writeFile(iteration);
    }
    SPDLOG_INFO("Iteration {} finished", iteration);
    current_time += arg.getDeltaT();
  }
}
