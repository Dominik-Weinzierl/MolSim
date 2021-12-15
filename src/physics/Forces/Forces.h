#pragma once

#include "particles/Particle.h"
/**
 * Forces class is a wrapper for a method that calculates additional gravitation and adds it to the force of a Particle.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class Forces {
 public:
  static inline void additionalGravitation(Particle<dim> &p, double &gravitation) {
    auto force = p.getF();
    force[1] += p.getM() * gravitation;
    p.setF(force);
  }
};
