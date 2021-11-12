#include <arguments/argument/Argument.h>
#include <iostream>
#include <simulation/variants/GravitationSimulation.h>
#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <outputWriter/XYZWriter/XYZWriter.h>
#include <arguments/argumentParser/ParserStrategy.h>
#include <arguments/argument/XMLArgument/XMLArgument.h>
#include <generator/variants/CuboidGenerator.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "fileReader/InputFile/InputReader.h"
#include "simulation/variants/LennardSimulation.h"

/*static void measureTime(const Argument &arg, OutputWriter &writer, ParticleContainer &particleContainer) {
  auto start = std::chrono::high_resolution_clock::now();
  LennardSimulation::performSimulation(arg, writer, particleContainer);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms";
}
*/

/**
 * Creates a parser which parses information based on the selected parser
 * (e.g. BasicArgumentParser parses arguments from the command line),
 * writes the VTK file and performs the simulation
 * @param argc
 * @param argv
 * @return Program exit.
 */
int main(int argc, char *argv[]) {

  auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("Logger", "log.txt");
  spdlog::set_default_logger(async_file);

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

  if (dynamic_cast<XMLArgument *>(arg.get()) != nullptr) {
    auto *xmlArgument = dynamic_cast<XMLArgument *>(arg.get());
    CuboidGenerator cuboidGenerator;

    for (auto &cuboidArgument: xmlArgument->getCuboidArguments()) {
      cuboidGenerator.generate(cuboidArgument, particleContainer);
    }
  }

  if (arg->getPhysics() == "gravitation") {
    GravitationSimulation::performSimulation(*arg, *writer, particleContainer);
  } else if (arg->getPhysics() == "lennard") {
    LennardSimulation::performSimulation(*arg, *writer, particleContainer);
  }
  //measureTime(*arg, *writer, particleContainer);
}

