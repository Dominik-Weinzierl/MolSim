#pragma once
#include <string>
#include <memory>
#include <outputWriter/OutputWriter.h>

/**
 * Argument stores the arguments parsed by ArgumentParser for easy access.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class Argument {
 private:
  /**
   * Stores additional input files used to fill the ParticleContainer.
   */
  std::vector<std::string> files;

  /**
   * Defines the end time of the simulation.
   */
  double endTime;

  /**
   * Defines the step width of our simulation.
   */
  double deltaT;

  /**
   * Defines the output file prefix of our simulation.
   */
  std::string output;

  /**
   * Defines the used writer for our simulation.
   */
  std::string writer;

  /**
   * Defines the used physic during our simulation.
   */
  std::string physics;

  /**
   * Defines the writing iteration of our simulation.
   */
  int iteration;

 public:
  virtual ~Argument() = default;

  /**
   * Argument constructor to construct Arguments provided by the ArgumentParser.
   * @param pFiles additional input files to load additional Particle
   * @param pEndTime end time of the simulation
   * @param pDeltaT time steps during the simulation
   * @param pOutput output file prefix
   * @param pWriter used writer to write in the output files
   * @param pIteration defines the writing iteration
   * @param pPhysics defines the used Physics during the simulation
   */
  Argument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput, std::string pWriter,
           int pIteration, std::string pPhysics) : files{std::move(pFiles)}, endTime{pEndTime}, deltaT{pDeltaT},
                                                   output{std::move(pOutput)}, writer{std::move(pWriter)},
                                                   physics{std::move(pPhysics)}, iteration{pIteration} {};

  /**
   * Getter for endTime.
   * @return double endTime
   */
  [[nodiscard]] double getEndTime() const {
    return endTime;
  }

  /**
   * Getter for deltaT.
   * @return double deltaT
   */
  [[nodiscard]] double getDeltaT() const {
    return deltaT;
  }

  /**
   * Getter for input files.
   * @return std::vector<std::string> files
   */
  [[nodiscard]] std::vector<std::string> getFiles() const {
    return files;
  }

  /**
   * Getter for iteration.
   * @return int iteration
   */
  [[nodiscard]] int getIteration() const {
    return iteration;
  }

  /**
   * Getter for output file prefix.
   * @return std::basic_string<char> output
   */
  [[nodiscard]] std::basic_string<char> getOutput() const {
    return output;
  }

  /**
   * Getter for selected writer (vtk/xyz).
   * @return std::basic_string<char> writer
   */
  [[nodiscard]] std::basic_string<char> getWriter() const {
    return writer;
  }

  /**
   * Getter for used physics (gravitation/lennard)
   * @return std::basic_string<char> physics
   */
  [[nodiscard]] std::basic_string<char> getPhysics() const {
    return physics;
  }

  /**
   * Used to create additional Particle based on input arguments.
   * @param container modified ParticleContainer.
   */
  virtual void createAdditionalParticle(ParticleContainer<dim> &container) const = 0;
};
