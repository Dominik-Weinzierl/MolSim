#pragma once

#include "particles/ParticleContainer.h"

/**
 * Physics is an abstract class which provides methods to calculate the next simulation step
 * based on the template method pattern.
 */
class Physics {
 protected:
  const Vector ZERO{};
  virtual ~Physics() = default;

  /**
   * Calculates and updates the position of all particles in the specified container.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT
   */
  virtual void calculateX(ParticleContainer &particleContainer, double deltaT) const = 0;

  /**
   * Calculates and updates the force for all particles in the specified container
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   */
  virtual void calculateF(ParticleContainer &particleContainer) const = 0;

  /**
   * Calculates and updates the velocity of all particles in the specified container.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT
   */
  virtual void calculateV(ParticleContainer &particleContainer, double deltaT) const = 0;

 public:

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer
   * @param deltaT
   */
  virtual void calculateNextStep(ParticleContainer &particleContainer, double deltaT) const = 0;
};