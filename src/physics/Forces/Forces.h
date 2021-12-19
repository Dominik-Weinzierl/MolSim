#pragma once

#include "particles/Particle.h"
/**
 * Forces class is a wrapper for a method that calculates additional gravitation and adds it to the force of a Particle.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class Forces {
 public:
  static inline double additionalGravitation(Particle<dim> &p, double &gravitation) {
    return p.getM() * gravitation;
  }
};
