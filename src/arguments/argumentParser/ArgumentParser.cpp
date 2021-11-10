#include "ArgumentParser.h"

#include <utility>
#include <utils/ArrayUtils.h>

ArgumentStatus::ArgumentStatus() {
  flags.insert({"filename", {false, "", ""}});
}

ArgumentParser::ArgumentParser(int argc, char **arguments) {
  for (int i = 1; i < argc; ++i) {
    tokens.emplace_back(arguments[i]);
  }
}

bool ArgumentStatus::validStatus() {
  return std::all_of(flags.begin(), flags.end(), [](auto v) {
    return std::get<0>(std::get<1>(v));
  });
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
                                const std::string &possibleValue) {
  status.updateFlag(name, flag, possibleValue);
}

void ArgumentParser::handleFlag(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                const std::string &possibleValue, std::vector<std::string> possibleValues) {
  if (std::find(possibleValues.begin(), possibleValues.end(), possibleValue) == possibleValues.end()) {
    throw std::invalid_argument("Expected: " + ArrayUtils::to_string(possibleValues) + " | Got: " + possibleValue);
  }
  status.updateFlag(name, flag, possibleValue);
}

template<>
void ArgumentParser::performCheck<int>(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                       const std::string &possibleValue) {
  try {
    status.updateFlag(name, flag, std::stoi(possibleValue));
  } catch (std::invalid_argument &e) {
    throw std::invalid_argument("Expected: int  | Got: " + possibleValue);
  }
}

template<>
void ArgumentParser::performCheck<double>(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                          const std::string &possibleValue) {
  try {
    status.updateFlag(name, flag, std::stod(possibleValue));
  } catch (std::invalid_argument &e) {
    throw std::invalid_argument("Expected: double  | Got: " + possibleValue);
  }
}

template<typename T>
void ArgumentParser::handleFlag(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                const std::string &possibleValue) {
  performCheck<T>(status, name, flag, possibleValue);
}

template<>
void ArgumentParser::handleFlag<int>(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                     const std::string &possibleValue) {
  performCheck<int>(status, name, flag, possibleValue);
}

template<>
void ArgumentParser::handleFlag<double>(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                        const std::string &possibleValue) {
  performCheck<double>(status, name, flag, possibleValue);
}
