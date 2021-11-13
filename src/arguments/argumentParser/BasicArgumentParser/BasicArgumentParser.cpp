#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF

#include <algorithm>
#include <iostream>
#include <arguments/argument/BasicArgument/BasicArgument.h>
#include "spdlog/spdlog.h"
#include <outputWriter/XYZWriter/XYZWriter.h>
#include "BasicArgumentParser.h"

//---------------------------Constructor---------------------------
BasicArgumentStatus::BasicArgumentStatus() : ArgumentStatus() {
  flags.insert({"endTime", {false, "", ""}});
  flags.insert({"deltaT", {false, "", ""}});
  flags.insert({"writer", {true, "default", std::string{"vtk"}}});
  flags.insert({"output", {true, "default", std::string{"MD_vtk"}}});
  flags.insert({"physics", {true, "default", std::string{"gravitation"}}});
  flags.insert({"iteration", {true, "default", 60}});
}

BasicArgumentParser::BasicArgumentParser(int argc, char **arguments) : ArgumentParser(argc, arguments) {

}

//---------------------------Methods---------------------------
bool BasicArgumentParser::validateInput() {
  for (auto it = tokens.begin(); it != tokens.end() && it + 1 != tokens.end(); ++it) {
    const auto &flag = *it;
    const auto &possibleValue = *(it + 1);

    if (flag == "-f" || flag == "--filename") {
      handleFlag(status, "filename", flag, possibleValue);
      it++;
    } else if (flag == "-o" || flag == "--output") {
      handleFlag(status, "output", flag, possibleValue);
      it++;
    } else if (flag == "-t" || flag == "--t_end") {
      handleFlag<double>(status, "endTime", flag, possibleValue);
      it++;
    } else if (flag == "-d" || flag == "--delta_t") {
      handleFlag<double>(status, "deltaT", flag, possibleValue);
      it++;
    } else if (flag == "-i" || flag == "--iteration") {
      handleFlag<int>(status, "iteration", flag, possibleValue);
      it++;
    } else if (flag == "-p" || flag == "--physics") {
      handleFlag(status, "physics", flag, possibleValue, {"gravitation", "lennard"});
      it++;
    } else if (flag == "-w" || flag == "--writer") {
      handleFlag(status, "writer", flag, possibleValue, {"vtk", "xyz"});
      it++;
    } else {
      throw std::invalid_argument("Invalid argument: " + flag);
    }
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