#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO

#include "ParticleContainer.h"

#include <utility>
#include <iostream>
#include "spdlog/spdlog.h"

//---------------------------Constructor---------------------------



ParticleContainer::ParticleContainer(std::vector<Particle> pParticles) : particles{std::move(pParticles)} {
  SPDLOG_TRACE("ParticleContainer generated");

}

ParticleContainer::ParticleContainer() : particles{} {
  SPDLOG_TRACE("ParticleContainer generated");
}

ParticleContainer::~ParticleContainer() {
  SPDLOG_TRACE("ParticleContainer destructed");
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

