#pragma once

#include "physics/Physics.h"

/**
 * The Gravitation class is a subclass of Physics and therefore implements the calculation methods
 * for the active force of all particles in the particleContainer.
 */
class Gravitation : public Physics {
 protected:

  /**
   * Calculates the force that is active on all particles via the simple force calculation
   * method given in the meeting for worksheet 1.
   * @param particleContainer
   */
  void calculateF(ParticleContainer &particleContainer) const override;
};
