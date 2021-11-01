#include "Simulation.h"

//! Performs the simulation
//! \param writer the way, in which files should be written
//! \param physics the physics to be used
//! \param particleContainer the initial particles
//! \param arg the command line-arguments
void Simulation::performSimulation(OutputWriter &writer, const Physics &physics, ParticleContainer &particleContainer,
                                   Argument &arg) {
  double current_time = start_time;
  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < arg.getEndTime()) {
    // calculate new x
    physics.calculateX(particleContainer, arg.getDeltaT());
    // calculate new f
    physics.calculateF(particleContainer);
    // calculate new v
    physics.calculateV(particleContainer, arg.getDeltaT());

    iteration++;

    std::cout << "Force: " << particleContainer.getParticles()[3].getF() << " | Position: "
              << particleContainer.getParticles()[3].getX() << " | Velocity: "
              << particleContainer.getParticles()[3].getV() << std::endl;

    if (iteration % 60 == 0) {
      writer.writeFile(iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;
    current_time += arg.getDeltaT();
  }
}
