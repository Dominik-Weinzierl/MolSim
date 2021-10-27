#include "ParticleContainer.h"

#include <utility>

//---------------------------Constructor---------------------------
ParticleContainer::ParticleContainer(std::list<Particle> particles) : particles{std::move(particles)} {
  for (const auto &particle: particles) {
    addParticleToPairs(particle);
  }
}

//---------------------------Methods---------------------------
const std::list<Particle> &ParticleContainer::getParticles() const {
  return particles;
}

const std::list<std::pair<Particle, Particle>> &ParticleContainer::getParticlePairs() const {
  return particlePairs;
}

void ParticleContainer::addParticle(const Particle &p) {
  addParticleToPairs(p);
  particles.emplace_back(p);
}

void ParticleContainer::addParticleToPairs(const Particle &p) {
  for (const auto &particle: particles) {
    particlePairs.emplace_back(p, particle);
  }
}

int ParticleContainer::size() const {
  return particles.size();
}


