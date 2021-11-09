#include "Argument.h"

#include <utility>

Argument::Argument(std::vector<std::string> files, double end_time, double delta_t, std::string output,
                   std::string writer, int iteration, std::string physics) : files{std::move(files)},
                                                                             end_time{end_time}, delta_t{delta_t},
                                                                             output{std::move(output)},
                                                                             writer{std::move(writer)},
                                                                             physics{std::move(physics)},
                                                                             iteration{iteration} {

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
