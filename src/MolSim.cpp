#include "fileReader/FileReader.h"
#include "MolSim.h"
#include "outputWriter/VTKWriter/VTKWriter.h"
#include <iostream>
#include <physics/gravitation/Gravitation.h>
#include <arguments/Argument/Argument.h>
#include <arguments/BasicArgumentParser/BasicArgumentParser.h>

void performSimulation(OutputWriter &writer, const Physics &physics, ParticleContainer &particleContainer,
                       Argument &arg) {
  double current_time = start_time;
  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < arg.getEndTime()) {
    // calculate new x
    physics.calculateX(particleContainer);
    // calculate new f
    physics.calculateF(particleContainer);
    // calculate new v
    physics.calculateV(particleContainer);

    iteration++;
    if (iteration % 10 == 0) {
      writer.writeFile(iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;
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
  VTKWriter writer{"MD_vtk", particleContainer};
  FileReader::readFile(particleContainer, arg.getFileName());

  performSimulation(writer, gravitation, particleContainer, arg);

  std::cout << "output written. Terminating..." << std::endl;

}