#pragma once
#include "logger/Logger.h"
#include "physics/Physics.h"

/**
 * The Gravitation class is a subclass of Physics and therefore implements the calculation methods
 * for the active force of all particles in the particleContainer.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class Gravitation : public Physics<dim> {
 private:

  /**
   * Updates the force of the Particle(s).
   * @param particleContainer container which contains the Particle(s) used for this simulation.
   */
  void performUpdate(ParticleContainer<dim> &particleContainer) const;
  // Since we expect only dim two or three, there is no default implementation required.
 public:

  /**
   * Calculates the force that is active on all particles via the simple force calculation method.
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