#pragma once

#include "particles/ParticleContainer.h"
#include "particles/Particle.h"

struct GeneratorArguments{};

class Generator {
 protected:
  Generator() = default;
  virtual ~Generator() = default;

 public:

  virtual void generate(GeneratorArguments& g, ParticleContainer &p) = 0;
  virtual void applyMotion(double meanValue, Particle &p) = 0;
};
