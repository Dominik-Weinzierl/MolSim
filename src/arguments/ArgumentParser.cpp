#include "ArgumentParser.h"

ArgumentStatus::ArgumentStatus() : inputFileName(std::make_tuple(false, "", "")),
                                   end_time{std::make_tuple(false, "", -1)}, delta_t{std::make_tuple(false, "", -1)} {
}
void ArgumentStatus::setDelta_t(const std::string &flag, const double &value) {
  std::get<0>(delta_t) = true;
  std::get<1>(delta_t) = flag;
  std::get<2>(delta_t) = value;
}
void ArgumentStatus::setEnd_time(const std::string &flag, const double &value) {
  std::get<0>(end_time) = true;
  std::get<1>(end_time) = flag;
  std::get<2>(end_time) = value;
}
void ArgumentStatus::setInputFileName(const std::string &flag, const std::string &value) {
  std::get<0>(inputFileName) = true;
  std::get<1>(inputFileName) = flag;
  std::get<2>(inputFileName) = value;
}

std::tuple<bool, std::string, std::string> &ArgumentStatus::getInputFileName() {
  return inputFileName;
}
std::tuple<bool, std::string, double> &ArgumentStatus::getEnd_time() {
  return end_time;
}
std::tuple<bool, std::string, double> &ArgumentStatus::getDelta_t() {
  return delta_t;
}
bool ArgumentStatus::validStatus() {
  return std::get<0>(inputFileName) && std::get<0>(end_time) && std::get<0>(delta_t);
}
