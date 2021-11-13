#include "Argument.h"

#include <utility>

Argument::Argument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
                   std::string pWriter, int pIteration, std::string pPhysics) : files{std::move(pFiles)},
                                                                                endTime{pEndTime}, deltaT{pDeltaT},
                                                                                output{std::move(pOutput)},
                                                                                writer{std::move(pWriter)},
                                                                                physics{std::move(pPhysics)},
                                                                                iteration{pIteration} {

}

double Argument::getEndTime() const {
  return endTime;
}

double Argument::getDeltaT() const {
  return deltaT;
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
