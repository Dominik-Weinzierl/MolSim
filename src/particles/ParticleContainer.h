#pragma once

#include "Particle.h"
#include <list>

class ParticleContainer {
 private:
  std::list<Particle> particles;
  std::list<std::pair<Particle, Particle>> particlePairs;

  void addParticleToPairs(const Particle &p);

 public:
  ParticleContainer();
  virtual ~ParticleContainer();
  explicit ParticleContainer(std::list<Particle> particles);

  void addParticle(const Particle &p);

  [[nodiscard]] const std::list<Particle> &getParticles() const;
  [[nodiscard]] const std::list<std::pair<Particle, Particle>> &getParticlePairs() const;

  [[nodiscard]] int size() const;
};