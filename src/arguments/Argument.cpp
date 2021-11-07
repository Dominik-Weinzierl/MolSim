#include "Argument.h"

#include <utility>

Argument::Argument(std::string inputFileName, double end_time, double delta_t, std::string output,
                   std::string writer, double iteration) : inputFileName{std::move(inputFileName)},
                                                                             end_time{end_time}, delta_t{delta_t},
                                                                             output{std::move(output)},
                                                                             writer{std::move(writer)},
                                                                             iteration{iteration} {

}


double Argument::getEndTime() const {
  return end_time;
}

double Argument::getDeltaT() const {
  return delta_t;
}

std::basic_string<char> Argument::getFileName() const {
  return inputFileName;
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
