#include "ArgumentParser.h"

#include <utility>

ArgumentStatus::ArgumentStatus() {
  flags.insert({"filename", {false, "", ""}});
}

bool ArgumentStatus::validStatus() {
  return std::get<0>(flags["filename"]);
}

void ArgumentStatus::updateFlag(const std::string &name, const std::string &flag,
                                std::variant<std::string, int, double> value) {
  std::get<0>(flags[name]) = true;
  std::get<1>(flags[name]) = flag;
  std::get<2>(flags[name]) = std::move(value);
}

std::variant<std::string, int, double> ArgumentStatus::getValue(const std::string &name) {
  return std::get<2>(flags[name]);
}

void ArgumentParser::handleFlag(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                const std::string &possibleValue, std::array<std::string, 2> flags) {
  if (flag == flags[0] || flag == flags[1]) {
    status.updateFlag(name, flag, possibleValue);
  }
}