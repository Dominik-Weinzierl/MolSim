#include "MolSim.h"

/**
 * Dimension of the current simulation.
 */
constexpr size_t dim = 2;

/**
 * Creates a parser which parses information based on the selected parser
 * (e.g. BasicArgumentParser parses arguments from the command line),
 * writes the VTK file and performs the simulation
 * @param argc
 * @param argv
 * @return Program exit code.
 */
int main(int argc, char *argv[]) {
  Logger::setupLogger();

  ParserStrategy<dim> strategy{argc, argv};

  if (argc == 1 || (std::string{argv[1]} == "-h" || std::string{argv[1]} == "--help")) {
    ParserStrategy<dim>::showUsage();
    return 0;
  }

  std::unique_ptr<ArgumentParser<dim>> parser = strategy.getParser();

  try {
    parser->validateInput();
  } catch (std::invalid_argument &exception) {
    std::cout << "[ERROR] " << exception.what() << std::endl;
    SPDLOG_ERROR(exception.what());
    ParserStrategy<dim>::showUsage();
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

  return MolSim<dim>::simulate(arg, writer, particleContainer);
}

