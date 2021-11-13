#include "Argument.h"

#include <utility>

Argument::Argument(std::vector<std::string> filesIn, double end_timeIn, double delta_tIn, std::string outputIn,
                   std::string writerIn, int iterationIn, std::string physicsIn) : files{std::move(filesIn)},
                                                                                   end_time{end_timeIn},
                                                                                   delta_t{delta_tIn},
                                                                                   output{std::move(outputIn)},
                                                                                   writer{std::move(writerIn)},
                                                                                   physics{std::move(physicsIn)},
                                                                                   iteration{iterationIn} {

}

double Argument::getEndTime() const {
  return end_time;
}

double Argument::getDeltaT() const {
  return delta_t;
}

std::vector<std::string> Argument::getFiles() const {
  return files;
}

int Argument::getIteration() const {
  return iteration;
}

std::basic_string<char> Argument::getOutput() const {
  return output;
}

std::basic_string<char> Argument::getWriter() const {
  return writer;
}

std::basic_string<char> Argument::getPhysics() const {
  return physics;
}
