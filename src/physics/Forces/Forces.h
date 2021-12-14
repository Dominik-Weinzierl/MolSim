#pragma once

#include "particles/Particle.h"
/**
 * Forces class is a wrapper for a method that calculates additional gravitation and adds it to the force of a Particle.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class Forces {
  static void additionalGravitation(Particle<dim> &p, double gravitation){
    p.getF()[1] += p.getMass() * gravitation;
  }
};
