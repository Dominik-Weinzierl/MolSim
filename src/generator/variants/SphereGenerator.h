#pragma once

#include "generator/Generator.h"

class SphereGenerator : public Generator {
 public:
  SphereGenerator() = default;
  void generate(GeneratorArguments &g, ParticleContainer &p) override;
  void applyMotion(double meanValue, Particle &p) override;
};
