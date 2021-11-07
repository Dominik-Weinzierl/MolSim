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

//---------------------------Methods---------------------------
bool BasicArgumentParser::validateInput() {
  status.setOutput("default", "MD_vtk");
  status.setWriter("default", "vtk");
  status.setIteration("default", 60);
  status.setPhysics("default", "gravitation");

  for (auto it = tokens.begin(); it != tokens.end() && it + 1 != tokens.end(); ++it) {
    const auto &flag = *it;
    const auto &possibleValue = *(it + 1);
    handleInputFileFlag(status, flag, possibleValue);
    handleEndTimeFlag(status, flag, possibleValue);
    handleDeltaTFlag(status, flag, possibleValue);
    handleOutputFlag(status, flag, possibleValue);
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
  std::unique_ptr<OutputWriter> writer;

  return std::make_unique<BasicArgument>(std::get<2>(status.getInputFileName()), std::get<2>(status.getEnd_time()),
                                         std::get<2>(status.getDelta_t()), std::get<2>(status.getOutput()),
                                         std::move(std::get<2>(status.getWriter())), std::get<2>(status.getIteration()),
                                         std::get<2>(status.getPhysics()));
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
  std::cout << usage.str();
}

void BasicArgumentParser::handleEndTimeFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                            const std::string &possibleValue) {
  if (flag == "-t" || flag == "--t_end") {
    try {
      argumentStatus.setEnd_time(flag, std::stod(possibleValue));
    } catch (std::invalid_argument &e) {
      throw std::invalid_argument("Expected: number | Got: " + possibleValue);
    }
  }
}

void BasicArgumentParser::handleDeltaTFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                           const std::string &possibleValue) {
  if (flag == "-d" || flag == "--delta_t") {
    try {
      argumentStatus.setDelta_t(flag, std::stod(possibleValue));
    } catch (std::invalid_argument &e) {
      throw std::invalid_argument("Expected: number | Got: " + possibleValue);
    }
  }
}

void BasicArgumentParser::handleWriterFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                           const std::string &possibleValue) {
  if (flag == "-w" || flag == "--writer") {
    if (possibleValue != "vtk" || possibleValue != "xyz") {
      throw std::invalid_argument("Expected: vtk or xyz | Got: " + possibleValue);
    }
    argumentStatus.setWriter(flag, possibleValue);
    argumentStatus.setOutput("default", "MD_" + possibleValue);
  }
}

void BasicArgumentParser::handleOutputFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                           const std::string &possibleValue) {
  if (flag == "-o" || flag == "--output") {
    argumentStatus.setOutput(flag, possibleValue);
  }
}

void BasicArgumentParser::handleIterationFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                              const std::string &possibleValue) {
  if (flag == "-i" || flag == "--iteration") {
    try {
      argumentStatus.setIteration(flag, std::stoi(possibleValue));
    } catch (std::invalid_argument &e) {
      throw std::invalid_argument("Expected: int | Got: " + possibleValue);
    }
  }
}
void BasicArgumentParser::handlePhysicsFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                            const std::string &possibleValue) {
  if (flag == "-p" || flag == "--physics") {
    if (possibleValue != "gravitation") {
      throw std::invalid_argument("Expected: gravitation | Got: " + possibleValue);
    }
    argumentStatus.setPhysics(flag, possibleValue);
  }
}

bool BasicArgumentStatus::validStatus() {
  return ArgumentStatus::validStatus() && std::get<0>(end_time) && std::get<0>(delta_t);
}

void BasicArgumentStatus::setDelta_t(const std::string &flag, const double &value) {
  std::get<0>(delta_t) = true;
  std::get<1>(delta_t) = flag;
  std::get<2>(delta_t) = value;
}
void BasicArgumentStatus::setEnd_time(const std::string &flag, const double &value) {
  std::get<0>(end_time) = true;
  std::get<1>(end_time) = flag;
  std::get<2>(end_time) = value;
}

std::tuple<bool, std::string, double> &BasicArgumentStatus::getEnd_time() {
  return end_time;
}

std::tuple<bool, std::string, double> &BasicArgumentStatus::getDelta_t() {
  return delta_t;
}

std::tuple<bool, std::string, std::string> &BasicArgumentStatus::getWriter() {
  return writer;
}

std::tuple<bool, std::string, std::string> &BasicArgumentStatus::getOutput() {
  return output;
}

std::tuple<bool, std::string, int> &BasicArgumentStatus::getIteration() {
  return iteration;
}

void BasicArgumentStatus::setWriter(const std::string &flag, const std::string &value) {
  std::get<0>(writer) = true;
  std::get<1>(writer) = flag;
  std::get<2>(writer) = value;
}

void BasicArgumentStatus::setOutput(const std::string &flag, const std::string &value) {
  std::get<0>(output) = true;
  std::get<1>(output) = flag;
  std::get<2>(output) = value;
}

void BasicArgumentStatus::setIteration(const std::string &flag, const int &value) {
  std::get<0>(iteration) = true;
  std::get<1>(iteration) = flag;
  std::get<2>(iteration) = value;
}

std::tuple<bool, std::string, std::string> &BasicArgumentStatus::getPhysics() {
  return physics;
}

void BasicArgumentStatus::setPhysics(const std::string &flag, const std::string &value) {
  std::get<0>(physics) = true;
  std::get<1>(physics) = flag;
  std::get<2>(physics) = value;
}
