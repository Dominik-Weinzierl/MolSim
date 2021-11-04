#include <arguments/Argument/Argument.h>
#include <arguments/ArgumentParser.h>
#include <arguments/BasicArgumentParser/BasicArgumentParser.h>
#include <iostream>
#include <simulation/variants/GravitationSimulation.h>
#include "fileReader/FileReader.h"

/**
 * Creates a parser which parses information based on the selected parser
 * (e.g. BasicArgumentParser parses arguments from the command line),
 * writes the VTK file and performs the simulation
 * @param argc
 * @param argv
 * @return Program exit.
 */
int main(int argc, char *argv[]) {
  BasicArgumentParser parser{argc, argv};
  ParserStatus status = parser.validateInput();

  if (argc == 1) {
    parser.showUsage();
    return 0;
  }

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
  VTKWriter writer{"MD_vtk", "output", particleContainer};
  FileReader::readFile(particleContainer, arg.getFileName());
  GravitationSimulation::performSimulation(arg, writer, particleContainer);
}

