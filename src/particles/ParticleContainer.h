#pragma once

#include "Particle.h"
#include <list>

class ParticleContainer {
 private:
  const std::list<Particle> particles;

 public:
   ParticleContainer();
   const std::list<Particle>& getParticles();
};