#pragma once
#include "logger/Logger.h"
#include "physics/Physics.h"

/**
 * The Gravitation class is a subclass of Physics and therefore implements the calculation methods
 * for the active force of all particles in the particleContainer.
 */
template<size_t dim>
class Gravitation : public Physics<dim> {
 private:
  void performUpdate(ParticleContainer<dim> &particleContainer) const;
 protected:

  /**
   * Calculates the force that is active on all particles via the simple force calculation
   * method given in the meeting for worksheet 1.
   * @param particleContainer
   */
  void calculateF(ParticleContainer<dim> &particleContainer) const override {
    SPDLOG_DEBUG("started calculating forces");
    for (auto &p: particleContainer) {
      p.setOldF(p.getF());
      p.setF(0, 0, 0);
    }
    performUpdate(particleContainer);
    SPDLOG_DEBUG("ended calculating forces");
  }
};