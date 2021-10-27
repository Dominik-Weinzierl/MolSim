#pragma once

#include "Particle.h"
#include <list>

class ParticleContainer {
 private:
  const std::list<Particle> particles{};

 public:
  ParticleContainer() = default;
  virtual ~ParticleContainer() = default;
  explicit ParticleContainer(std::list<Particle> particles);

  [[nodiscard]] const std::list<Particle> &getParticles() const;
};