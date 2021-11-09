#include <algorithm>
#include <iostream>
#include <arguments/argument/BasicArgument/BasicArgument.h>
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
    handleFlag<double>(status, "endTime", flag, possibleValue, {"-t", "--t_end"});
    handleFlag<double>(status, "deltaT", flag, possibleValue, {"-d", "--delta_t"});
    handleFlag<int>(status, "iteration", flag, possibleValue, {"-i", "--iteration"});
    handleFlag(status, "physics", flag, possibleValue, {"-p", "--physics"}, {"gravitation"});
    handleFlag(status, "writer", flag, possibleValue, {"-w", "--writer"}, {"vtk", "xyz"});
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

  return std::make_unique<BasicArgument>(std::vector<std::string>{filename}, endTime, deltaT, output, writer, iteration,
                                         physics);
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

bool BasicArgumentStatus::validStatus() {
  return ArgumentStatus::validStatus() && std::all_of(flags.begin(), flags.end(), [](auto v) {
    return std::get<0>(std::get<1>(v));
  });
}
