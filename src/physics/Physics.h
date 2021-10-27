#pragma once

#include "particles/ParticleContainer.h"

class Physics {
 public:
  /**
  * calculate the force for all particles
  */
  void calculateF(const ParticleContainer &particleContainer);

  /**
  * calculate the position for all particles
  */
  void calculateX(const ParticleContainer &particleContainer);
  /**
  * calculate the velocity for all particles
  */
  void calculateV(const ParticleContainer &particleContainer);
};
