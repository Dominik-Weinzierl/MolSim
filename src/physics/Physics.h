#pragma once

#include "particles/ParticleContainer.h"

//! Physics is an abstract class which provides methods to calculate the next simulation step.
//! Based on the template method pattern.
class Physics {
 protected:
  const Vector ZERO{};
  virtual ~Physics() = default;

  //! calculates and updates the position of all particles in the specified container
  //! \param particleContainer the ParticleContainer, for whose contents the positions should be calculated
  virtual void calculateX(ParticleContainer &particleContainer, double deltaT) const = 0;

  //! calculates and updates the force for all particles in the specified container
  //! \param particleContainer the ParticleContainer, for whose contents the forces should be calculated
  virtual void calculateF(ParticleContainer &particleContainer) const = 0;

  //! calculates and updates the velocity of all particles in the specified container
  //! \param particleContainer the ParticleContainer, for whose contents the velocity should be calculated
  virtual void calculateV(ParticleContainer &particleContainer, double deltaT) const = 0;

 public:
  virtual void calculateNextStep(ParticleContainer &particleContainer, double deltaT) const = 0;
};