#include "logger/Logger.h"

#include <arguments/argument/Argument.h>
#include <iostream>
#include <outputWriter/XYZWriter/XYZWriter.h>
#include <arguments/argumentParser/ParserStrategy.h>
#include "fileReader/InputFile/InputReader.h"
#include <iomanip>
#include "simulation/MDSimulation.h"
#include "physics/LennardJones/LennardJones.h"

constexpr size_t dim = 2;

static void measureTime(const Argument<dim> &arg, OutputWriter<dim> &writer,
                        ParticleContainer<dim> &particleContainer) {
  auto start = std::chrono::high_resolution_clock::now();
  MDSimulation<LennardJones<dim>, dim>::performSimulation(writer, particleContainer, arg);
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms";
}

/**
 * Creates a parser which parses information based on the selected parser
 * (e.g. BasicArgumentParser parses arguments from the command line),
 * writes the VTK file and performs the simulation
 * @param argc
 * @param argv
 * @return Program exit.
 */
int main(int argc, char *argv[]) {
  Logger::setupLogger();
  ParserStrategy<dim> strategy{argc, argv};

  if (argc == 1) {
    ParserStrategy<dim>::showUsage();
    return 0;
  }

  std::unique_ptr<ArgumentParser<dim>> parser = strategy.getParser();

  try {
    parser->validateInput();
  } catch (std::invalid_argument &exception) {
    std::cout << "[ERROR] " << exception.what() << std::endl;
    SPDLOG_ERROR(exception.what());
    parser->showUsage();
    return -1;
  }

  std::unique_ptr<Argument<dim>> arg = parser->createArgument();
  std::unique_ptr<OutputWriter<dim>> writer;
  ParticleContainer<dim> particleContainer;

  if (arg->getWriter() == "vtk") {
    writer = std::make_unique<VTKWriter<dim>>(arg->getOutput(), "output", particleContainer);
  } else if (arg->getWriter() == "xyz") {
    writer = std::make_unique<XYZWriter<dim>>(arg->getOutput(), "output", particleContainer);
  }

  for (const auto &file: arg->getFiles()) {
    InputReader<dim>::readFile(particleContainer, file);
  }

  arg->createAdditionalParticle(particleContainer);

  /*if (arg->getPhysics() == "gravitation") {
    MDSimulation<Gravitation<dim>, dim>::performSimulation(*writer, particleContainer, *arg);
  } else if (arg->getPhysics() == "lennard") {
    MDSimulation<LennardJones<dim>, dim>::performSimulation(*writer, particleContainer, *arg);
  }*/

  measureTime(*arg, *writer, particleContainer);
}

