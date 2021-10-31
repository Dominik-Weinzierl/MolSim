#include <algorithm>
#include <iostream>
#include <sstream>
#include "BasicArgumentParser.h"

//---------------------------Constructor---------------------------
BasicArgumentParser::BasicArgumentParser(int argc, char *arguments[]) {
  for (int i = 1; i < argc; ++i) {
    tokens.emplace_back(arguments[i]);
  }
  std::cout << "BasicArgumentParser generated!" << std::endl;
}

BasicArgumentParser::~BasicArgumentParser() {
  std::cout << "BasicArgumentParser destructed!" << std::endl;
}

//---------------------------Methods---------------------------
ParserStatus BasicArgumentParser::validateInput() {
  if ((argumentOptionIsAvailable("-h") || argumentOptionIsAvailable("--help")) && tokens.size() == 1) {
    return Operation_Help;
  }
  if (!argumentOptionIsAvailable("-f") && !argumentOptionIsAvailable("--filename")) {
    return Error_MissingArgument;
  }
  if (!argumentOptionIsAvailable("-t") && !argumentOptionIsAvailable("--t_end")) {
    return Error_MissingArgument;
  }
  if (!argumentOptionIsAvailable("-d") && !argumentOptionIsAvailable("--delta_t")) {
    return Error_MissingArgument;
  }
  if (tokens.size() != 6) {
    return Error_InvalidOperation;
  }
  return Operation_Simulation;
}

std::optional<std::string> BasicArgumentParser::getValueOfArgumentOption(const std::string &option) const {
  for (auto it = tokens.begin(); it != tokens.end(); ++it) {
    if (option == *it) {
      return {*(++it)};
    }
  }
  return std::nullopt;
}

bool BasicArgumentParser::argumentOptionIsAvailable(const std::string &option) const {
  return std::find(tokens.begin(), tokens.end(), option) != this->tokens.end();
}

Argument BasicArgumentParser::createArgument() {
  auto filename = getValueOfArgumentOption("-f");
  if (!filename.has_value()) {
    filename = getValueOfArgumentOption("--filename");
  }

  auto t_end = getValueOfArgumentOption("-t");
  if (!t_end.has_value()) {
    t_end = getValueOfArgumentOption("--t_end");
  }

  auto delta_t = getValueOfArgumentOption("-d");
  if (!delta_t.has_value()) {
    delta_t = getValueOfArgumentOption("--delta_t");
  }
  return {filename.value(), std::stod(t_end.value()), std::stod(delta_t.value())};
}

void BasicArgumentParser::showUsage() {
  std::stringstream usage;
  usage << "Usage: " << "./molsym" << std::endl;
  usage << "Options:" << std::endl;
  usage << "\t-h,--help\t\tShow this help message" << std::endl;
  usage << "\t-f,--filename\t\tSpecify the end time of this simulation" << std::endl;
  usage << "\t-t,--t_end\t\tSpecify the end time of this simulation" << std::endl;
  usage << "\t-d,--delta_t\t\tSpecify the time steps per calculation" << std::endl;
  std::cout << usage.str();
}
