#pragma once

#include "logger/Logger.h"
#include "physics/Physics.h"

/**
 * This class implements gravitational physics.
 */
class Gravitation : public PhysicsType {
 public:

  //----------------------------------------Methods----------------------------------------

  /**
   * Calculates Force according to the worksheet between two given Particles.
   * @tparam dim Dimension of the simulation
   * @param i One of the Particles
   * @param j Other Particle
   * @return calculated Force
   */
  template<size_t dim>
  static inline Vector<dim> calculateForceBetweenTwoParticles(Particle<dim> &i, Particle<dim> &j) {
    Vector<dim> force{};
    double m = i.getM() * j.getM();

    Vector<dim> difference = j.getX() - i.getX();
    double l2Norm = ArrayUtils::L2Norm(difference);

    double factor = m / (l2Norm * l2Norm * l2Norm);

    for (size_t t = 0; t < dim; ++t) {
      force[t] = factor * difference[t];
    }

    return force;
  }
};
