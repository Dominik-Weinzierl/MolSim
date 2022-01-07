#pragma once

#include "physics/Physics.h"

/**
 * This class implements the HarmonicPotential.
 */
class HarmonicPotential : public PhysicsType {
 private:

 public:

  //----------------------------------------Methods----------------------------------------

  template<size_t dim>
  static inline Vector<dim> calculateForceBetweenTwoParticles(Particle<dim> *i, Particle<dim> *j, double &l2Norm) {
    return i->getMembraneArguments()[0] * (l2Norm - i->getMembraneArguments()[1]) * ((j->getX() - i->getX()) / l2Norm);
  }

  template<size_t dim>
  static inline Vector<dim> calculateForceBetweenTwoDiagonalParticles(Particle<dim> *i, Particle<dim> *j,
                                                                      double &l2Norm) {
    // TODO replace magic number
    return i->getMembraneArguments()[0] * (l2Norm - 1.41421356237 * i->getMembraneArguments()[1])
        * ((j->getX() - i->getX()) / l2Norm);
  }
};