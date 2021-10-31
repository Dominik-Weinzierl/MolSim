#include "ParticleContainer.h"

#include <utility>
#include <iostream>

//---------------------------Constructor---------------------------
ParticleContainer::ParticleContainer(std::vector<Particle> particles) : particles{std::move(particles)} {
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
std::vector<Particle> &ParticleContainer::getParticles() {
  return particles;
}

std::vector<std::pair<Particle &, Particle &>> &ParticleContainer::getParticlePairs() {
  return particlePairs;
}

void ParticleContainer::addParticle(const Particle& p) {
  particles.emplace_back(p);
  addParticleToPairs(particles.back());
}

void ParticleContainer::addParticleToPairs(Particle &p) {
  for (auto &particle: particles) {
    if (&p != &particle) {
      particlePairs.emplace_back(particle, p);
    }
  }
}

unsigned long ParticleContainer::size() const {
  return particles.size();
}

