#pragma once
#include <string>
#include <arguments/argument/Argument.h>

template<size_t dim>
class BasicArgument : public Argument<dim> {
 public:
  /**
   * BasicArgument constructor to construct Arguments provided by the ArgumentParser.
   * @param pFiles
   * @param pEndTime
   * @param pDeltaT
   * @param pOutput
   * @param pWriter
   * @param pIteration
   * @param pPhysics
   */
  BasicArgument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
                std::string pWriter, int pIteration, std::string pPhysics) : Argument<dim>(std::move(pFiles), pEndTime,
                                                                                           pDeltaT, std::move(pOutput),
                                                                                           std::move(pWriter),
                                                                                           pIteration,
                                                                                           std::move(pPhysics)) {

  }

  void createAdditionalParticle(ParticleContainer<dim> &container) const override {
    (void) container;
  }
};
