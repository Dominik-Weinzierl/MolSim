#pragma once
#include <string>
#include <memory>
#include <outputWriter/OutputWriter.h>
/**
 * Argument stores the arguments parsed by ArgumentParser for easy access.
 */
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
           int pIteration, std::string pPhysics);

  [[nodiscard]] double getEndTime() const;

  [[nodiscard]] double getDeltaT() const;

  [[nodiscard]] std::vector<std::string> getFiles() const;

  [[nodiscard]] int getIteration() const;

  [[nodiscard]] std::basic_string<char> getOutput() const;

  [[nodiscard]] std::basic_string<char> getWriter() const;

  [[nodiscard]] std::basic_string<char> getPhysics() const;

  virtual void createAdditionalParticle(ParticleContainer& container) const = 0;
};
