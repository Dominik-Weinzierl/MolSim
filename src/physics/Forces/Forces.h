#pragma once

#include "particles/Particle.h"

/**
 * Forces class is a wrapper for a method that calculates additional gravitation and adds it to the force of a Particle.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class Forces {
 public:

  //----------------------------------------Methods----------------------------------------

  /**
   * Additional gravitation which is applied in each iteration.
   * @param p Particle
   * @param gravitation Vector with additional force
   * @return force scaled with the mass
   */
  static inline Vector<dim> additionalGravitation(Particle<dim> &p, Vector<dim> &gravitation) {

    //gravity along the axis is set, other axes should be zero (0*M = 0)
    return p.getM() * gravitation;
  }
};
