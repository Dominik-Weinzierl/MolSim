#pragma once

#include "physics/Physics.h"

/**
 * The Gravitation class is a subclass of Physics and therefore implements the calculation methods
 * for the active force, position and velocity of all particles in the particleContainer.
 */
class Gravitation : public Physics {
 protected:

  /**
   * Calculates the position via the Velocity-Strömer-Verlet-Algorithm given in the meeting for worksheet 1.
   * @param particleContainer
   * @param deltaT
   */
  void calculateX(ParticleContainer &particleContainer, double deltaT) const override;

  /**
   * Calculates the force that is active on all particles via the simple force calculation
   * method given in the meeting for worksheet 1.
   * @param particleContainer
   */
  void calculateF(ParticleContainer &particleContainer) const override;

  /**
   * Calculates the velocity via the Velocity-Strömer-Verlet-Algorithm given in the meeting for worksheet 1.
   * @param particleContainer
   * @param deltaT
   */
  void calculateV(ParticleContainer &particleContainer, double deltaT) const override;

 public:

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer
   * @param deltaT
   */
  void calculateNextStep(ParticleContainer &particleContainer, double deltaT) const override;
};
