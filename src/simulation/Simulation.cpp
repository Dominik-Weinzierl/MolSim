#include <spdlog/spdlog.h>
#include "Simulation.h"

void Simulation::performSimulation(__attribute__((unused))OutputWriter &writer, const Physics &physics,
                                   ParticleContainer &particleContainer, const Argument &arg) {
  double current_time = start_time;
  int iteration = 0;
  auto deltaT = arg.getDeltaT();

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < arg.getEndTime()) {
    physics.calculateNextStep(particleContainer, deltaT);

    if (iteration % arg.getIteration() == 0) {
      writer.writeFile(iteration);
    }

    SPDLOG_INFO("Iteration {} finished", iteration);
    iteration++;
    current_time += deltaT;
  }
}
