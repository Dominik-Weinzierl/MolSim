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
  virtual void calculateF(const ParticleContainer &particleContainer);

  /**
  * calculate the position for all particles
  */
  virtual void calculateX(const ParticleContainer &particleContainer);
  /**
  * calculate the velocity for all particles
  */
  virtual void calculateV(const ParticleContainer &particleContainer);
};
