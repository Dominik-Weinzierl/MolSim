#include "ParticleContainer.h"

#include <utility>
#include <iostream>

//---------------------------Constructor---------------------------
ParticleContainer::ParticleContainer(std::list<Particle> particles) : particles{std::move(particles)} {
  for (auto &particle: particles) {
    addParticleToPairs(particle);
  }
  std::cout << "ParticleContainer generated!" << std::endl;
}

ParticleContainer::ParticleContainer() : particles{}, particlePairs{} {
  std::cout << "ParticleContainer generated!" << std::endl;
}

ParticleContainer::~ParticleContainer() {
  std::cout << "ParticleContainer destructed!" << std::endl;
}

//---------------------------Methods---------------------------
std::list<Particle> &ParticleContainer::getParticles() {
  return particles;
}

std::list<std::pair<Particle, Particle>> &ParticleContainer::getParticlePairs() {
  return particlePairs;
}

void ParticleContainer::addParticle(Particle p) {
  addParticleToPairs(p);
  particles.push_back(p);
}

void ParticleContainer::addParticleToPairs(Particle &p) {
  for (const auto &particle: particles) {
    particlePairs.emplace_back(p, particle);
  }
}

int ParticleContainer::size() const {
  return particles.size();
}

