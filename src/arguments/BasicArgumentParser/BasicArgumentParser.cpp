#include <algorithm>
#include <iostream>
#include <sstream>
#include <arguments/BasicArgument/BasicArgument.h>
#include "BasicArgumentParser.h"

//---------------------------Constructor---------------------------
BasicArgumentParser::BasicArgumentParser(int argc, char *arguments[]) : ArgumentParser() {
  for (int i = 1; i < argc; ++i) {
    tokens.emplace_back(arguments[i]);
  }
  //std::cout << "BasicArgumentParser generated!" << std::endl;
}

//---------------------------Methods---------------------------
bool BasicArgumentParser::validateInput() {
  bool invalid = false;
  for (auto it = tokens.begin(); it != tokens.end() && it + 1 != tokens.end(); ++it) {
    if (*it == "-f" || *it == "--filename") {
      status.setInputFileName(*it, *(it + 1));
    } else if (*it == "-t" || *it == "--t_end") {
      try {
        status.setEnd_time(*it, std::stod(*(it + 1)));
      } catch (std::invalid_argument &e) {
        std::cout << "Erroneous programme call! " << std::endl;
        std::cout << "ERROR: End time needs to be a double, but is " << *(it + 1) << std::endl;
        invalid = true;
        break;
      }
    } else if (*it == "-d" || *it == "--delta_t") {
      try {
        status.setDelta_t(*it, std::stod(*(it + 1)));
      } catch (std::invalid_argument &e) {
        std::cout << "Erroneous programme call! " << std::endl;
        std::cout << "ERROR: Delta t needs to be a double, but is " << *(it + 1) << std::endl;
        invalid = true;
        break;
      }
    }
  }
  if (tokens.size() < 6 || invalid || !status.validStatus()) {
    return false;
  }
  return true;
}

std::unique_ptr<Argument> BasicArgumentParser::createArgument() {
  return std::make_unique<BasicArgument>(std::get<2>(status.getInputFileName()), std::get<2>(status.getEnd_time()),
                                         std::get<2>(status.getDelta_t()));
}

void BasicArgumentParser::showUsage() {
  std::stringstream usage;
  usage << "Usage: " << "./MolSim" << std::endl;
  usage << "Options:" << std::endl;
  usage << "\t-h,--help\t\tShow this help message" << std::endl;
  usage << "\t-f,--filename\t\tSpecify the input filename" << std::endl;
  usage << "\t-t,--t_end\t\tSpecify the end time of this simulation" << std::endl;
  usage << "\t-d,--delta_t\t\tSpecify the time steps per calculation" << std::endl;
  std::cout << usage.str();
}
