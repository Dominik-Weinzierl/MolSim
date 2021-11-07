#include <arguments/Argument.h>
#include <arguments/BasicArgumentParser/BasicArgumentParser.h>
#include <iostream>
#include <simulation/variants/GravitationSimulation.h>
#include <spdlog/spdlog.h>
#include <outputWriter/XYZWriter/XYZWriter.h>
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

  if (argc == 1) {
    parser.showUsage();
    return 0;
  }

  try {
    parser.validateInput();
  } catch (std::invalid_argument &exception) {
    std::cout << "[ERROR] " << exception.what() << std::endl;
    SPDLOG_ERROR(exception.what());
    parser.showUsage();
    return -1;
  }

  std::unique_ptr<Argument> arg = parser.createArgument();
  std::unique_ptr<OutputWriter> writer;
  ParticleContainer particleContainer;

  if (arg->getWriter() == "vtk") {
    writer = std::make_unique<VTKWriter>(arg->getOutput(), "output", particleContainer);
  } else if (arg->getWriter() == "xyz") {
    writer = std::make_unique<XYZWriter>(arg->getOutput(), "output", particleContainer);
  }

  FileReader::readFile(particleContainer, arg->getFileName());
  GravitationSimulation::performSimulation(*arg, *writer, particleContainer);
}

