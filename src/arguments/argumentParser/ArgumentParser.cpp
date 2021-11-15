#include "ArgumentParser.h"

template<>
template<>
void ArgumentParser<2>::performCheck<int>(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                          const std::string &possibleValue) {
  try {
    status.updateFlag(name, flag, std::stoi(possibleValue));
  } catch (std::invalid_argument &e) {
    throw std::invalid_argument("Expected: int  | Got: " + possibleValue);
  }
}

template<>
template<>
void ArgumentParser<3>::performCheck<int>(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                          const std::string &possibleValue) {
  try {
    status.updateFlag(name, flag, std::stoi(possibleValue));
  } catch (std::invalid_argument &e) {
    throw std::invalid_argument("Expected: int  | Got: " + possibleValue);
  }
}

template<>
template<>
void ArgumentParser<2>::performCheck<double>(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                             const std::string &possibleValue) {
  try {
    status.updateFlag(name, flag, std::stod(possibleValue));
  } catch (std::invalid_argument &e) {
    throw std::invalid_argument("Expected: double  | Got: " + possibleValue);
  }
}

template<>
template<>
void ArgumentParser<3>::performCheck<double>(ArgumentStatus &status, const std::string &name, const std::string &flag,
                                             const std::string &possibleValue) {
  try {
    status.updateFlag(name, flag, std::stod(possibleValue));
  } catch (std::invalid_argument &e) {
    throw std::invalid_argument("Expected: double  | Got: " + possibleValue);
  }
}

