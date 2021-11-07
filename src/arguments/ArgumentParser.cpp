#include "ArgumentParser.h"

void ArgumentStatus::setInputFileName(const std::string &flag, const std::string &value) {
  std::get<0>(inputFileName) = true;
  std::get<1>(inputFileName) = flag;
  std::get<2>(inputFileName) = value;
}

std::tuple<bool, std::string, std::string> &ArgumentStatus::getInputFileName() {
  return inputFileName;
}

bool ArgumentStatus::validStatus() {
  return std::get<0>(inputFileName);
}

void ArgumentParser::handleInputFileFlag(ArgumentStatus &status, const std::string &flag,
                                         const std::string &possibleValue) {
  if (flag == "-f" || flag == "--filename") {
    status.setInputFileName(flag, possibleValue);
  }
}
