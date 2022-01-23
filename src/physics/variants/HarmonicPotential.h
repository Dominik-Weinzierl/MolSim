#pragma once

#include "physics/Physics.h"

/**
 * This class implements the HarmonicPotential.
 */
class HarmonicPotential : public PhysicsType {
 public:

  //----------------------------------------Methods----------------------------------------

  /**
   * Calculates HarmonicPotential according to the worksheet between two given Particles.
   * @tparam dim Dimension of the simulation
   * @param i One of the Particles
   * @param j Other Particle
   * @param l2Norm Distance between the Particles
   * @return Calculated Harmonic Potential
   */
  template<size_t dim>
  static inline Vector<dim> calculateForceBetweenTwoParticles(Particle<dim> *i, Particle<dim> *j, double &l2Norm) {
    return i->getMembraneArguments()[0] * (l2Norm - i->getMembraneArguments()[1]) * ((j->getX() - i->getX()) / l2Norm);
  }

  /**
   * Calculates HarmonicPotential according to the worksheet between two given diagonal Particles.
   * @tparam dim Dimension of the simulation
   * @param i One of the Particles
   * @param j Other Particle
   * @param l2Norm Distance between the Particles
   * @return Calculated Harmonic Potential
   */
  template<size_t dim>
  static inline Vector<dim> calculateForceBetweenTwoDiagonalParticles(Particle<dim> *i, Particle<dim> *j,
                                                                      double &l2Norm) {
    //1.41421356237 == sqrt(2)
    return i->getMembraneArguments()[0] * (l2Norm - 1.41421356237 * i->getMembraneArguments()[1])
        * ((j->getX() - i->getX()) / l2Norm);
  }
};