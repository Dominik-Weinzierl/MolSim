#pragma once

#include "particles/ParticleContainer.h"

class Physics {
 private:

 public:
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
};
