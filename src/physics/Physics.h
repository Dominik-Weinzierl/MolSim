#pragma once

#include "particles/ParticleContainer.h"

class Physics {
 private:

 public:
  Physics() = default;
  virtual ~Physics() = default;

  /**
  * calculate the force for all particles
  */
  virtual void calculateF(ParticleContainer &particleContainer) const = 0;

  /**
  * calculate the position for all particles
  */
  virtual void calculateX(ParticleContainer &particleContainer, double deltaT) const = 0;
  /**
  * calculate the velocity for all particles
  */
  virtual void calculateV(ParticleContainer &particleContainer, double deltaT) const = 0;
};
