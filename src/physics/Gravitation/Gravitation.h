#pragma once

#include "physics/Physics.h"

//! The Gravitation class is a subclass of Physics and therefore implements the calculation methods
//! for the active force, position and velocity of all particles in the particleContainer
class Gravitation : public Physics {
 public:
  //! Calculates the position via the Velocity-Strömer-Verlet-Algorithm given
  //! in the meeting for worksheet 1
  void calculateX(ParticleContainer &particleContainer, double deltaT) const override;
  //! Calculates the force that is active on
  //! all particles via the simple force calculation method given in the meeting for worksheet 1
  void calculateF(ParticleContainer &particleContainer) const override;
  //! Calculates the velocity via the Velocity-Strömer-Verlet-Algorithm given
  //! in the meeting for worksheet 1
  void calculateV(ParticleContainer &particleContainer, double deltaT) const override;
};
