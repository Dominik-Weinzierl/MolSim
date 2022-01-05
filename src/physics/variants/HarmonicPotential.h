#pragma once

#include "physics/Physics.h"

/**
 * This class implements the HarmonicPotential.
 */
class HarmonicPotential : public PhysicsType {
 public:

  //----------------------------------------Methods----------------------------------------

  template<size_t dim>
  static inline Vector<dim> calculateForceBetweenTwoParticles(Particle<dim> &i, Particle<dim> &j, double &l2Norm) {
    return i.getMembraneArguments()[0] * (l2Norm - i.getMembraneArguments()[1]) * (j.getX() - i.getX());
  }

  template<size_t dim>
  static inline Vector<dim> calculateForceBetweenTwoDiagonalParticles(Particle<dim> &i, Particle<dim> &j, double &l2Norm) {
    return i.getMembraneArguments()[0] * (l2Norm - std::pow(2, 0.5)*i.getMembraneArguments()[1]) * (j.getX() - i.getX());
  }
};