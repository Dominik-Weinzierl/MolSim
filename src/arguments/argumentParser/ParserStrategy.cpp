#include <arguments/argumentParser/XMLArgumentParser/XMLArgumentParser.h>
#include <arguments/argumentParser/BasicArgumentParser/BasicArgumentParser.h>
#include <sstream>
#include <iostream>
#include "ParserStrategy.h"

std::unique_ptr<ArgumentParser> ParserStrategy::getParser() {
  return std::move(parser);
}

ParserStrategy::ParserStrategy(int argc, char *argv[]) {
  if (argc > 1) {
    if (std::string{argv[1]} == "-x" || std::string{argv[1]} == "--xml") {
      parser = std::make_unique<XMLArgumentParser>(argc, argv);
    } else {
      parser = std::make_unique<BasicArgumentParser>(argc, argv);
    }
  }
}

void ParserStrategy::showUsage() {
  std::stringstream usage;
  usage << "Usage: " << "./MolSim " << std::endl;
  usage << "Options:" << std::endl;
  usage << "\t-h,--help\t\tShow this help message" << std::endl;
  usage << "\t-f,--filename\t\tSpecify the input filename" << std::endl;
  usage << "\t-t,--t_end\t\tSpecify the end time of this simulation" << std::endl;
  usage << "\t-d,--delta_t\t\tSpecify the time steps per calculation" << std::endl;
  usage << "\t-o,--output\t\tSpecify the output filename" << std::endl;
  usage << "\t-i,--iteration\t\tSpecify the iteration" << std::endl;
  usage << "\t-w,--writer\t\tSpecify the writer used for the output files" << std::endl;
  usage << "\t-p,--physics\t\tSpecify the physics used for the simulation" << std::endl;
  usage << std::endl;
  usage << "Usage: " << "./MolSim [-x | --xml]" << std::endl;
  usage << "Options:" << std::endl;
  usage << "\t-h,--help\t\tShow this help message" << std::endl;
  usage << "\t-f,--filename\t\tSpecify the input filename as xml" << std::endl;
  std::cout << usage.str();
}
