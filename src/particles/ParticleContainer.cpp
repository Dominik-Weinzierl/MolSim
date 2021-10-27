#include "ParticleContainer.h"

#include <utility>

//---------------------------Constructor---------------------------
ParticleContainer::ParticleContainer(std::list<Particle> particles) : particles{std::move(particles)} {
}

//---------------------------Methods---------------------------
const std::list<Particle> &ParticleContainer::getParticles() const {
  return particles;
}


