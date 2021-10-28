#include <iostream>
#include <sstream>
#include "ArgumentParser.h"
#include <algorithm>

ArgumentParser::ArgumentParser(int argc, char *arguments[]) {
  for (int i = 1; i < argc; ++i) {
    tokens.emplace_back(arguments[i]);
  }
  std::cout << "ArgumentParser generated!" << std::endl;
}

ArgumentParser::~ArgumentParser() {
  std::cout << "ArgumentParser destructed!" << std::endl;
}

bool ArgumentParser::validateInput() {
  if ((argumentOptionIsAvailable("-h") || argumentOptionIsAvailable("--help")) && tokens.size() != 1) {
    std::cout << "Help should be used without any additional arguments" << std::endl;
    return false;
  } else {
    if (!argumentOptionIsAvailable("-f") || !argumentOptionIsAvailable("--filename")) {
      return false;
    }
    if (!argumentOptionIsAvailable("-t") || !argumentOptionIsAvailable("--t_end")) {
      return false;
    }
    if (!argumentOptionIsAvailable("-d") || !argumentOptionIsAvailable("--delta_t")) {
      return false;
    }
    if (tokens.size() != 6) {
      return false;
    }
  }
  return true;
}

void ArgumentParser::showUsage() {
  std::stringstream usage;
  usage << "Usage: " << "./molsym" << std::endl;
  usage << "Options:" << std::endl;
  usage << "\t-h,--help\t\t\tShow this help message" << std::endl;
  usage << "\t-f,--filename\t\tSpecify the end time of this simulation" << std::endl;
  usage << "\t-t,--t_end\t\t\tSpecify the end time of this simulation" << std::endl;
  usage << "\t-d,--delta_t\t\tSpecify the time steps per calculation" << std::endl;
  std::cout << usage.str();
}

std::optional<std::string> ArgumentParser::getValueOfArgumentOption(const std::string &option) const {
  for (auto it = tokens.begin(); it != tokens.end(); ++it) {
    if (option == *it) {
      return {*(++it)};
    }
  }
  return std::nullopt;
}

bool ArgumentParser::argumentOptionIsAvailable(const std::string &option) const {
  return std::find(tokens.begin(), tokens.end(), option) != this->tokens.end();
}

Argument ArgumentParser::createArgument() {
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
