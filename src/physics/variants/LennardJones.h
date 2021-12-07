#pragma once

#include "physics/Physics.h"

/**
 * This class implements the Lennard-Jones potential.
 */
class LennardJones : public PhysicsType {
 public:
  template<size_t dim>
  static inline Vector<dim> calculateForceBetweenTwoParticles(Particle<dim> &i, Particle<dim> &j, double &l2Norm) {
    Vector<dim> diff{i.getX() - j.getX()};

    double fracture = (i.getZeroCrossing() * j.getZeroCrossing()) / l2Norm;

    double firstFactor = (24 * i.getPotentialWellDepth()) / l2Norm;
    double pow = fracture * fracture * fracture;
    double secondFactor = pow - 2 * pow * pow;
    double factor = firstFactor * secondFactor;

    for (size_t t = 0; t < dim; ++t) {
      diff[t] *= -factor;
    }

    return diff;
  }
};