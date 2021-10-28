#include <iostream>
#include <utility>
#include "Argument.h"

Argument::~Argument() {
  std::cout << "Argument destructed!" << std::endl;
}
Argument::Argument(std::string inputFileName, double end_time, double delta_t) : inputFileName{
    std::move(inputFileName)}, end_time{end_time}, delta_t{delta_t} {

}
double Argument::getEndTime() const {
  return end_time;
}
double Argument::getDeltaT() const {
  return delta_t;
}
