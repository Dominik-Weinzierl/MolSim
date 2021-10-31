#pragma once

#include "Particle.h"
#include <list>

class ParticleContainer {
 private:
  std::list<Particle> particles;
  std::list<std::pair<Particle&, Particle&>> particlePairs;

  void addParticleToPairs(Particle &p);

 public:
  ParticleContainer();
  virtual ~ParticleContainer();
  explicit ParticleContainer(std::list<Particle> particles);

  void addParticle(const Particle& p);

  [[nodiscard]] std::list<Particle> &getParticles();
  [[nodiscard]] std::list<std::pair<Particle&, Particle&>> &getParticlePairs();

  [[nodiscard]] int size() const;
};