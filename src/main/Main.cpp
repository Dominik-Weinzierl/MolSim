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
  std::vector<std::string> args(argv + 1, argv + argc);

  Logger::setupLogger();

  ParserStrategy<dim> strategy{args};

  if (argc == 1 || (std::string{args[0]} == "-h" || std::string{args[0]} == "--help")) {
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

  std::cout << "Configuration loaded..." << std::endl;
  arg->toString();

  if (std::find(args.begin(), args.end(), "-b") != args.end()
      || std::find(args.begin(), args.end(), "--benchmark") != args.end()) {
    std::cout << "Perform benchmarks..." << std::endl;
    return MolSim<dim>::benchmark(arg, particleContainer);
  } else {
    std::cout << "Perform simulation... " << std::endl;
    return MolSim<dim>::simulate(arg, writer, particleContainer);
  }

}

