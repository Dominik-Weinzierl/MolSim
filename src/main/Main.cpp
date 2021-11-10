#include <arguments/argument/Argument.h>
#include <iostream>
#include <simulation/variants/GravitationSimulation.h>
#include <spdlog/spdlog.h>
#include <outputWriter/XYZWriter/XYZWriter.h>
#include <arguments/argumentParser/ParserStrategy.h>
#include "fileReader/InputFile/InputReader.h"

/**
 * Creates a parser which parses information based on the selected parser
 * (e.g. BasicArgumentParser parses arguments from the command line),
 * writes the VTK file and performs the simulation
 * @param argc
 * @param argv
 * @return Program exit.
 */
int main(int argc, char *argv[]) {
  ParserStrategy strategy{argc, argv};

  if (argc == 1) {
    ParserStrategy::showUsage();
    return 0;
  }

  std::unique_ptr<ArgumentParser> parser = strategy.getParser();

  try {
    parser->validateInput();
  } catch (std::invalid_argument &exception) {
    std::cout << "[ERROR] " << exception.what() << std::endl;
    SPDLOG_ERROR(exception.what());
    parser->showUsage();
    return -1;
  }

  std::unique_ptr<Argument> arg = parser->createArgument();
  std::unique_ptr<OutputWriter> writer;
  ParticleContainer particleContainer;

  if (arg->getWriter() == "vtk") {
    writer = std::make_unique<VTKWriter>(arg->getOutput(), "output", particleContainer);
  } else if (arg->getWriter() == "xyz") {
    writer = std::make_unique<XYZWriter>(arg->getOutput(), "output", particleContainer);
  }

  for (const auto &file: arg->getFiles()) {
    InputReader::readFile(particleContainer, file);
  }

  if (arg->getPhysics() == "gravitation") {
    GravitationSimulation::performSimulation(*arg, *writer, particleContainer);
  }
}

