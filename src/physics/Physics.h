#pragma once

#include "particles/ParticleContainer.h"

/**
 * Physics is an abstract class which provides methods to calculate the next simulation step
 * based on the template method pattern.
 */
template<size_t dim>
class Physics {
 protected:
  virtual ~Physics() = default;

  /**
   * Calculates and updates the position of all particles in the specified container.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT
   */
  static void calculateX(ParticleContainer<dim> &particleContainer, double deltaT);

  /**
   * Calculates and updates the force for all particles in the specified container
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   */
  virtual void calculateF(ParticleContainer<dim> &particleContainer) const = 0;

  /**
   * Calculates and updates the velocity of all particles in the specified container.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT
   */
  static void calculateV(ParticleContainer<dim> &particleContainer, double deltaT);

 public:

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer
   * @param deltaT
   */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT) const {
    // calculate new x
    calculateX(particleContainer, deltaT);
    // calculate new f
    calculateF(particleContainer);
    // calculate new v
    calculateV(particleContainer, deltaT);
  }
};

