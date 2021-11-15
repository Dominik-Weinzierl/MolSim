#pragma once
#include <string>
#include <memory>
#include <outputWriter/OutputWriter.h>
/**
 * Argument stores the arguments parsed by ArgumentParser for easy access.
 */
template<size_t dim>
class Argument {

 private:
  std::vector<std::string> files;
  double endTime;
  double deltaT;
  std::string output;
  std::string writer;
  std::string physics;
  int iteration;

 public:
  virtual ~Argument() = default;

  /**
   * Argument constructor to construct Arguments provided by the ArgumentParser.
   * @param pFiles
   * @param pEndTime
   * @param pDeltaT
   * @param pOutput
   * @param pWriter
   * @param pIteration
   * @param pPhysics
   */
  Argument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput, std::string pWriter,
           int pIteration, std::string pPhysics) : files{std::move(pFiles)}, endTime{pEndTime}, deltaT{pDeltaT},
                                                   output{std::move(pOutput)}, writer{std::move(pWriter)},
                                                   physics{std::move(pPhysics)}, iteration{pIteration} {};

  [[nodiscard]] double getEndTime() const {
    return endTime;
  }

  [[nodiscard]] double getDeltaT() const {
    return deltaT;
  }

  [[nodiscard]] std::vector<std::string> getFiles() const {
    return files;
  }

  [[nodiscard]] int getIteration() const {
    return iteration;
  }

  [[nodiscard]] std::basic_string<char> getOutput() const {
    return output;
  }

  [[nodiscard]] std::basic_string<char> getWriter() const {
    return writer;
  }

  [[nodiscard]] std::basic_string<char> getPhysics() const {
    return physics;
  }

  virtual void createAdditionalParticle(ParticleContainer<dim> &container) const = 0;
};
