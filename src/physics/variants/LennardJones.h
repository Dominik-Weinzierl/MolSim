#pragma once

#include "physics/Physics.h"

class LennardJones : public PhysicsType {
 public:
  template<size_t dim>
  static inline Vector<dim> calculateForceBetweenTwoParticles(Particle<dim> &i, Particle<dim> &j) {
    Vector<dim> force{i.getX() - j.getX()};
    double l2Norm = 0.0;

    for (size_t t = 0; t < dim; ++t) {
      l2Norm += force[t] * force[t];
    }

    double fracture = (i.getZeroCrossing() * j.getZeroCrossing()) / l2Norm;

    double firstFactor = (24 * i.getPotentialWellDepth()) / l2Norm;
    double pow = fracture * fracture * fracture;
    double secondFactor = pow - 2 * pow * pow;
    double factor = firstFactor * secondFactor;

    for (size_t t = 0; t < dim; ++t) {
      force[t] *= -factor;
    }

    return force;
  }
};