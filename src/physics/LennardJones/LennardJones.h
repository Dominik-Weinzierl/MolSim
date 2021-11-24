#pragma once

#include "physics/Vector/Vector.h"
#include "particles/ParticleContainer.h"
#include "physics/Physics.h"
#include <utils/ArrayUtils.h>
#include "logger/Logger.h"

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
  [[nodiscard]] inline double calculateFactor(const Vector<dim> &diff) const {
    double l2Norm = 0.0;

    for (size_t t = 0; t < dim; ++t) {
      l2Norm += diff[t] * diff[t];
    }

    double fracture = (zeroCrossing * zeroCrossing) / l2Norm;

    double firstFactor = (24 * potentialWellDepth) / (l2Norm);
    double pow = fracture * fracture * fracture;
    double secondFactor = pow - 2 * pow * pow;
    return firstFactor * secondFactor;
  }

  /**
   * Updates the force of the Particle(s).
   * @param particleContainer container which contains the Particle(s) used for this simulation.
   */
  void performUpdate(ParticleContainer<dim> &particleContainer) const {
    for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
      for (auto j = i + 1; j != particleContainer.end(); ++j) {
        SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());

        Vector<dim> force{i->getX() - j->getX()};
        double factor = calculateFactor(force);

        for (size_t t = 0; t < dim; ++t) {
          force[t] *= -factor;
        }

        i->updateForce(force);
        j->updateForce(-force);
      }
    }
  }

 public:

  /**
   * Calculates the new force value.
   * @param particleContainer container which contains the Particle(s) used for this simulation.
   */
  void calculateF(ParticleContainer<dim> &particleContainer) const override {
    Vector<dim> temp;
    SPDLOG_DEBUG("started calculating forces");
    for (auto &p: particleContainer) {
      p.setOldF(p.getF());
      p.setF(temp);
    }
    performUpdate(particleContainer);
    SPDLOG_DEBUG("ended calculating forces");
  }
};