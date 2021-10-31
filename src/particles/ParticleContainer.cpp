#include "ParticleContainer.h"

#include <utility>
#include <iostream>

//---------------------------Constructor---------------------------
ParticleContainer::ParticleContainer(std::vector<Particle> particles) : particles{std::move(particles)} {
  std::cout << "ParticleContainer generated!" << std::endl;
}

ParticleContainer::ParticleContainer() : particles{} {
  std::cout << "ParticleContainer generated!" << std::endl;
}

ParticleContainer::~ParticleContainer() {
  std::cout << "ParticleContainer destructed!" << std::endl;
}

//---------------------------Methods---------------------------
std::vector<Particle> &ParticleContainer::getParticles() {
  return particles;
}

void ParticleContainer::addParticle(const Particle& p) {
  particles.emplace_back(p);
}

unsigned long ParticleContainer::size() const {
  return particles.size();
}

