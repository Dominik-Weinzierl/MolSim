#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <utility>
#include <optional>

#include "outputWriter/OutputWriter.h"
#include "thermostat/Thermostat.h"
#include "outputWriter/ProfileWriter/ProfileWriter.h"
#include "outputWriter/ProfileWriter/DummyProfileWriter.h"
#include "physics/Forces/Force.h"

/**
 * Argument stores the arguments parsed by ArgumentParser for easy access.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class Argument {
 protected:
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

  /**
   * Stores the strategy used by this simulation.
   */
  std::string strategy;

  /**
   *
   */
  std::unique_ptr<Thermostat<dim>> thermostat;

  /**
 * Stores the profile writer
 */
  std::unique_ptr<ProfileWriter<dim>> profileWriter;

  /**
   * Stores the additional gravitation
   */
  Vector<dim> additionalGravitation;

  /**
   * Column vector which stores the additional force with the according start and endTime.
   */
  std::vector<Force<dim>> forces;

 public:
  //----------------------------------------Constructor & Destructor----------------------------------------

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
   * @param pStrategy defines the used strategy for this simulation (direct vs linked cell)
   * @param pThermostat optional thermostat which is applied during the simulation
   * @param pProfileWriter optional profile writer
   * @param pAdditionalGravitation optional additional gravitation
   * @param pForces Vector of optional additional force
   */
  Argument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput, std::string pWriter,
           int pIteration, std::string pPhysics, std::string pStrategy, std::unique_ptr<Thermostat<dim>> pThermostat,
           std::unique_ptr<ProfileWriter<dim>> pProfileWriter, Vector<dim> pAdditionalGravitation,
           std::vector<Force<dim>> pForces) : files{std::move(pFiles)}, endTime{pEndTime}, deltaT{pDeltaT},
                                              output{std::move(pOutput)}, writer{std::move(pWriter)},
                                              physics{std::move(pPhysics)}, iteration{pIteration},
                                              strategy{std::move(pStrategy)}, thermostat{std::move(pThermostat)},
                                              profileWriter{std::move(pProfileWriter)},
                                              additionalGravitation{pAdditionalGravitation}, forces{pForces} {};

  //----------------------------------------Methods----------------------------------------

  /**
   * Used to create additional Particle based on input arguments.
   * @param container modified ParticleContainer.
   */
  virtual void createAdditionalParticle(ParticleContainer<dim> &container) const = 0;

  /**
  * Prints the arguments.
  */
  [[nodiscard]] virtual std::string toString() const {
    SPDLOG_TRACE("Argument->toString()");
    std::stringstream configuration;
    configuration << "\tAdditional input files:" << std::endl;
    for (const auto &f: this->files) {
      configuration << "\t\t" << f << std::endl;
    }
    configuration << "\tEnd time: " << this->getEndTime() << std::endl;;
    configuration << "\tDelta t: " << this->getDeltaT() << std::endl;
    configuration << "\tOutput file prefix: " << this->getOutput() << std::endl;
    configuration << "\tFile writer: " << this->getWriter() << std::endl;
    configuration << "\tIteration: " << this->getIteration() << std::endl;
    configuration << "\tPhysic: " << this->getPhysics() << std::endl;
    configuration << "\tAdditional gravitation: " << ArrayUtils::to_string(this->getAdditionalGravitation())
                  << std::endl;
    configuration << "\tForce: " << ArrayUtils::to_string(this->getForces()) << std::endl;
    configuration << "\tStrategy: " << this->strategy << std::endl;
    return configuration.str();
  }

  /**
   * Stream operator for CuboidArgument(s).
   * @tparam dim dimension of our simulation.
   * @param stream std::ostream
   * @param p CuboidArgument to print
   * @return updated stream
   */
  friend std::ostream &operator<<(std::ostream &stream, const Argument<dim> &c) {
    SPDLOG_TRACE("Argument->operator<<");
    stream << c.toString();
    return stream;
  }

  /**
   * Equality operator.
   * @param rhs Argument
   * @return true if the provided Argument has the same values
   */
  bool operator==(const Argument &rhs) const {
    return files == rhs.files && endTime == rhs.endTime && deltaT == rhs.deltaT && output == rhs.output
        && writer == rhs.writer && physics == rhs.physics && iteration == rhs.iteration && strategy == rhs.strategy
        && thermostat == rhs.thermostat && profileWriter == rhs.profileWriter
        && additionalGravitation == rhs.additionalGravitation && forces == rhs.forces;
  }

  /**
   * Inequality operator.
   * @param rhs Argument
   * @return true if the provided Argument has not the same values
   */
  bool operator!=(const Argument &rhs) const {
    return !(rhs == *this);
  }


  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * Getter for endTime.
   * @return double endTime
   */
  [[nodiscard]] double getEndTime() const {
    SPDLOG_TRACE("Argument->getEndTime(): {}", endTime);
    return endTime;
  }

  /**
   * Getter for deltaT.
   * @return double deltaT
   */
  [[nodiscard]] double getDeltaT() const {
    SPDLOG_TRACE("Argument->getDeltaT(): {}", deltaT);
    return deltaT;
  }

  /**
   * Getter for input files.
   * @return std::vector<std::string> files
   */
  [[nodiscard]] std::vector<std::string> getFiles() const {
    SPDLOG_TRACE("Argument->getFiles(): {}", ArrayUtils::to_string(files));
    return files;
  }

  /**
   * Getter for iteration.
   * @return int iteration
   */
  [[nodiscard]] int getIteration() const {
    SPDLOG_TRACE("Argument->getIteration(): {}", iteration);
    return iteration;
  }

  /**
   * Getter for output file prefix.
   * @return std::basic_string<char> output
   */
  [[nodiscard]] std::basic_string<char> getOutput() const {
    SPDLOG_TRACE("Argument->getOutput(): {}", output);
    return output;
  }

  /**
   * Getter for selected writer (vtk/xyz).
   * @return std::basic_string<char> writer
   */
  [[nodiscard]] std::basic_string<char> getWriter() const {
    SPDLOG_TRACE("Argument->getWriter(): {}", writer);
    return writer;
  }

  /**
   * Getter for used physics (gravitation/lennard)
   * @return std::basic_string<char> physics
   */
  [[nodiscard]] std::basic_string<char> getPhysics() const {
    SPDLOG_TRACE("Argument->getPhysics(): {}", physics);
    return physics;
  }

  /**
   * Getter for strategy.
   * @return strategy.
   */
  [[nodiscard]] const std::string &getStrategy() const {
    SPDLOG_TRACE("Argument->getStrategy(): {}", strategy);
    return strategy;
  }

  /**
   * Getter for thermostat.
   * @return thermostat.
   */
  [[nodiscard]] const std::unique_ptr<Thermostat<dim>> &getThermostat() const {
    return thermostat;
  }

  /**
   * Getter for profile writer.
   * @return profile writer.
   */
  [[nodiscard]] const std::unique_ptr<ProfileWriter<dim>> &getProfileWriter() const {
    return profileWriter;
  }

  /**
 * Getter for thermostat.
 * @return thermostat.
 */
  [[nodiscard]]  std::unique_ptr<Thermostat<dim>> &getThermostat() {
    return thermostat;
  }

  /**
   * Getter for profile writer.
   * @return profile writer.
   */
  [[nodiscard]]  std::unique_ptr<ProfileWriter<dim>> &getProfileWriter() {
    return profileWriter;
  }

  /**
   * Getter for gravitation.
   * @return gravitation.
   */
  [[nodiscard]] const Vector<dim> &getAdditionalGravitation() const {
    return additionalGravitation;
  }

  /**
   * Getter for forces.
   * @return forces
   */
  [[nodiscard]] const std::vector<Force<dim>> &getForces() const {
    return forces;
  }
};
