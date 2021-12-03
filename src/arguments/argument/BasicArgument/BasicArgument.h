#pragma once

#include <string>
#include <iostream>

#include "arguments/argument/Argument.h"

/**
 * BasicArgument stores the arguments parsed by BasicArgumentParser for easy access.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class BasicArgument : public Argument<dim> {
 public:
  /**
   * BasicArgument constructor to construct Arguments provided by the ArgumentParser (BasicArgumentParser).
   * @param pFiles additional input files to load additional Particle
   * @param pEndTime end time of the simulation
   * @param pDeltaT time steps during the simulation
   * @param pOutput output file prefix
   * @param pWriter used writer to write in the output files
   * @param pIteration defines the writing iteration
   * @param pPhysics defines the used Physics during the simulation
   * @param pStrategy defines the used strategy to perform this simulation (direct vs linked cell)
   */
  BasicArgument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
                std::string pWriter, int pIteration, std::string pPhysics, std::string pStrategy) : Argument<dim>(
      std::move(pFiles), pEndTime, pDeltaT, std::move(pOutput), std::move(pWriter), pIteration, std::move(pPhysics),
      pStrategy) {

  }

  /**
   * There are no additional ways to create additional particles via the command line.
   * If you want to create additional particles, you must use an xml configuration file.
   * @param container the ParticleContainer in which the current particles are stored.
   */
  void createAdditionalParticle(ParticleContainer<dim> &container) const override {
    (void) container;
  }
};

/**
 * Compare operator for BasicArgument(s);
 * @tparam dim dimension of simulation
 * @param left first BasicArgument
 * @param right second BasicArgument
 * @return true if all values are equal
 */
template<size_t dim>
bool operator==(const BasicArgument<dim> &left, const BasicArgument<dim> &right) {
  return left.getFiles() == right.getFiles() && left.getEndTime() == right.getEndTime()
      && left.getDeltaT() == right.getDeltaT() && left.getOutput() == right.getOutput()
      && left.getWriter() == right.getWriter() && left.getIteration() == right.getIteration()
      && left.getPhysics() == right.getPhysics() && left.getStrategy() == right.getStrategy();
}
