#include "ParticleContainer.h"

#include <utility>
#include <iostream>
#include <spdlog/spdlog.h>

//---------------------------Constructor---------------------------
ParticleContainer::ParticleContainer(std::vector<Particle> particles) : particles{std::move(particles)} {
  // SPDLOG_INFO("ParticleContainer generated");
}

ParticleContainer::ParticleContainer() : particles{} {
  // SPDLOG_INFO("ParticleContainer generated");
}

ParticleContainer::~ParticleContainer() {
  // SPDLOG_INFO("ParticleContainer destructed");
}

//---------------------------Methods---------------------------
std::vector<Particle> &ParticleContainer::getParticles() {
  return particles;
}

void ParticleContainer::addParticle(Particle p) {
  particles.push_back(std::move(p));
}

unsigned long ParticleContainer::size() const {
  return particles.size();
}

Particle &ParticleContainer::operator[](unsigned long i) {
  return particles[i];
}

Particle ParticleContainer::operator[](unsigned long i) const {
  return particles[i];
}

