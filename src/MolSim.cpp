#include "fileReader/FileReader.h"
#include "MolSim.h"
#include "outputWriter/VTKWriter/VTKWriter.h"
#include <iostream>
#include <physics/gravitation/Gravitation.h>
#include <arguments/Argument/Argument.h>
#include <arguments/BasicArgumentParser/BasicArgumentParser.h>

//! Performs the simulation
//! \param writer the way, in which files should be written
//! \param physics the physics to be used
//! \param particleContainer the initial particles
//! \param arg the command line-arguments
void performSimulation(OutputWriter &writer, const Physics &physics, ParticleContainer &particleContainer,
                       Argument &arg) {
  double current_time = start_time;
  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < arg.getEndTime()) {
    // calculate new f
    physics.calculateF(particleContainer);
    // calculate new x
    physics.calculateX(particleContainer, arg.getDeltaT());
    // calculate new v
    physics.calculateV(particleContainer, arg.getDeltaT());

    iteration++;
    if (iteration % 10 == 0) {
      writer.writeFile(iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;
    current_time += arg.getDeltaT();
  }
}

void performSimulationTest(const Physics &physics, ParticleContainer &particleContainer, Argument &arg) {
  double current_time = start_time;
  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < arg.getEndTime()) {
    // calculate new f
    physics.calculateF(particleContainer);
    iteration++;
    //std::cout << std::endl;
    for (const auto &p: particleContainer.getParticles()) {
      std::cout << p.getF() << std::endl;
    }
    //std::cout << std::endl;
    current_time += arg.getDeltaT();
  }
}

int main(int argc, char *argv[]) {
  BasicArgumentParser parser{argc, argv};
  ParserStatus status = parser.validateInput();

  if (status == ParserStatus::Operation_Help) {
    parser.showUsage();
    return 0;
  }

  if (status != ParserStatus::Operation_Simulation) {
    std::cout << "Erroneous programme call! " << std::endl;
    parser.showUsage();
    return -1;
  }

  Argument arg = parser.createArgument();
  ParticleContainer particleContainer;

  Gravitation gravitation;
  VTKWriter writer{"MD_vtk", "output", particleContainer};
  FileReader::readFile(particleContainer, arg.getFileName());

  performSimulation(writer, gravitation, particleContainer, arg);
  //Particle p1{{0, 0, 0}, {1, 1, 1}, 1};
  //Particle p2{{1, 1, 1}, {1, 1, 1}, 1};
  //particleContainer.addParticle(p1);
  //particleContainer.addParticle(p2);

  //performSimulationTest(gravitation, particleContainer, arg);

  std::cout << "output written. Terminating..." << std::endl;

}