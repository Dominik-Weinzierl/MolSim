#include <algorithm>
#include <iostream>
#include <arguments/BasicArgument/BasicArgument.h>
#include <spdlog/spdlog.h>
#include <outputWriter/XYZWriter/XYZWriter.h>
#include "BasicArgumentParser.h"

//---------------------------Constructor---------------------------
BasicArgumentParser::BasicArgumentParser(int argc, char *arguments[]) : ArgumentParser() {
  for (int i = 1; i < argc; ++i) {
    tokens.emplace_back(arguments[i]);
  }
  SPDLOG_INFO("BasicArgumentParser generated");
}

BasicArgumentStatus::BasicArgumentStatus() : ArgumentStatus() {
  flags.insert({"endTime", {false, "", ""}});
  flags.insert({"deltaT", {false, "", ""}});
  flags.insert({"writer", {true, "default", std::string{"vtk"}}});
  flags.insert({"output", {true, "default", std::string{"MD_vtk"}}});
  flags.insert({"physics", {true, "default", std::string{"gravitation"}}});
  flags.insert({"iteration", {true, "default", 60}});
}

//---------------------------Methods---------------------------
bool BasicArgumentParser::validateInput() {
  for (auto it = tokens.begin(); it != tokens.end() && it + 1 != tokens.end(); ++it) {
    const auto &flag = *it;
    const auto &possibleValue = *(it + 1);
    handleFlag(status, "filename", flag, possibleValue, {"-f", "--filename"});
    handleFlag(status, "output", flag, possibleValue, {"-o", "--output"});
    handleEndTimeFlag(status, flag, possibleValue);
    handleDeltaTFlag(status, flag, possibleValue);
    handleIterationFlag(status, flag, possibleValue);
    handleWriterFlag(status, flag, possibleValue);
    handlePhysicsFlag(status, flag, possibleValue);
  }
  if (!status.validStatus()) {
    throw std::invalid_argument("Missing required argument. Please check your arguments!");
  }
  return true;
}

std::unique_ptr<Argument> BasicArgumentParser::createArgument() {
  auto filename = std::get<std::string>(status.getValue("filename"));
  auto endTime = std::get<double>(status.getValue("endTime"));
  auto deltaT = std::get<double>(status.getValue("deltaT"));
  auto output = std::get<std::string>(status.getValue("output"));
  auto writer = std::get<std::string>(status.getValue("writer"));
  auto iteration = std::get<int>(status.getValue("iteration"));
  auto physics = std::get<std::string>(status.getValue("physics"));

  return std::make_unique<BasicArgument>(filename, endTime, deltaT, output, writer, iteration, physics);
}

void BasicArgumentParser::showUsage() {
  std::stringstream usage;
  usage << "Usage: " << "./MolSim" << std::endl;
  usage << "Options:" << std::endl;
  usage << "\t-h,--help\t\tShow this help message" << std::endl;
  usage << "\t-f,--filename\t\tSpecify the input filename" << std::endl;
  usage << "\t-t,--t_end\t\tSpecify the end time of this simulation" << std::endl;
  usage << "\t-d,--delta_t\t\tSpecify the time steps per calculation" << std::endl;
  usage << "\t-o,--output\t\tSpecify the output filename" << std::endl;
  usage << "\t-i,--iteration\t\tSpecify the iteration" << std::endl;
  usage << "\t-w,--writer\t\tSpecify the writer used for the output files" << std::endl;
  usage << "\t-p,--physics\t\tSpecify the physics used for the simulation" << std::endl;
  std::cout << usage.str();
}

void BasicArgumentParser::handleEndTimeFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                            const std::string &possibleValue) {
  if (flag == "-t" || flag == "--t_end") {
    try {
      argumentStatus.updateFlag("endTime", flag, std::stod(possibleValue));
    } catch (std::invalid_argument &e) {
      throw std::invalid_argument("Expected: number | Got: " + possibleValue);
    }
  }
}

void BasicArgumentParser::handleDeltaTFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                           const std::string &possibleValue) {
  if (flag == "-d" || flag == "--delta_t") {
    try {
      argumentStatus.updateFlag("deltaT", flag, std::stod(possibleValue));
    } catch (std::invalid_argument &e) {
      throw std::invalid_argument("Expected: number | Got: " + possibleValue);
    }
  }
}

void BasicArgumentParser::handleIterationFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                              const std::string &possibleValue) {
  if (flag == "-i" || flag == "--iteration") {
    try {
      argumentStatus.updateFlag("iteration", flag, std::stoi(possibleValue));
    } catch (std::invalid_argument &e) {
      throw std::invalid_argument("Expected: int | Got: " + possibleValue);
    }
  }
}

void BasicArgumentParser::handleWriterFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                           const std::string &possibleValue) {
  if (flag == "-w" || flag == "--writer") {
    if (possibleValue != "vtk" || possibleValue != "xyz") {
      throw std::invalid_argument("Expected: vtk or xyz | Got: " + possibleValue);
    }
    argumentStatus.updateFlag("writer", flag, possibleValue);
    argumentStatus.updateFlag("output", "default", "MD_" + possibleValue);
  }
}

void BasicArgumentParser::handlePhysicsFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                            const std::string &possibleValue) {
  if (flag == "-p" || flag == "--physics") {
    if (possibleValue != "gravitation") {
      throw std::invalid_argument("Expected: gravitation | Got: " + possibleValue);
    }
    argumentStatus.updateFlag("physics", flag, possibleValue);
  }
}

bool BasicArgumentStatus::validStatus() {
  return ArgumentStatus::validStatus() && std::all_of(flags.begin(), flags.end(), [](auto v) {
    return std::get<0>(std::get<1>(v));
  });
}
