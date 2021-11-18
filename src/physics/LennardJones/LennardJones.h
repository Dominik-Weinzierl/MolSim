#pragma once

#include "physics/Vector/Vector.h"
#include "particles/ParticleContainer.h"
#include "physics/Physics.h"
#include <utils/ArrayUtils.h>

/**
 * Contains force calculations based on the lennard jones potential.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class LennardJones : public Physics<dim> {
 private:
  /**
   * A zero-crossing is a point where the sign of a mathematical function changes.
   */
  double zeroCrossing = 1;

  /**
   * A potential well is the region surrounding a local minimum of potential energy.
   */
  double potentialWellDepth = 5;

  /**
   * Calculates the factor used to scale the differences of the two Particle(s).
   * @param diff difference between two Particle(s).
   * @return factor
   */
  [[nodiscard]] inline double calculateFactor(const Vector<dim> &diff) const;
  // Since we expect only dim two or three, there is no default implementation required.

  /**
   * Updates the force of the Particle(s).
   * @param particleContainer container which contains the Particle(s) used for this simulation.
   */
  void performUpdate(ParticleContainer<dim> &particleContainer) const;
  // Since we expect only dim two or three, there is no default implementation required.

 public:

  /**
   * Calculates the new force value.
   * @param particleContainer container which contains the Particle(s) used for this simulation.
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