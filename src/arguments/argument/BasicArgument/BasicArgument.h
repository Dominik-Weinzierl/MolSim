#pragma once
#include <string>
#include <arguments/argument/Argument.h>

/**
 * BasicArgument stores the arguments parsed by BasicArgumentParser for easy access.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class BasicArgument : public Argument<dim> {
 public:
  /**
   * BasicArgument constructor to construct Arguments provided by the ArgumentParser (BasicArgumentParser).
   * @param pFiles additional inout files to load Particle
   * @param pEndTime end time of the simulation
   * @param pDeltaT time steps during the simulation
   * @param pOutput output file prefix
   * @param pWriter used writer to write in the output files
   * @param pIteration defines the writing iteration
   * @param pPhysics defines the used Physics during the simulation
   */
  BasicArgument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
                std::string pWriter, int pIteration, std::string pPhysics) : Argument<dim>(std::move(pFiles), pEndTime,
                                                                                           pDeltaT, std::move(pOutput),
                                                                                           std::move(pWriter),
                                                                                           pIteration,
                                                                                           std::move(pPhysics)) {

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
