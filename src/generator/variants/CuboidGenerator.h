#pragma once

#include "generator/Generator.h"

class CuboidGenerator : public Generator {
 public:
  CuboidGenerator() = default;
  void generate(GeneratorArguments &g, ParticleContainer &p) override;
  void applyMotion(double meanValue, Particle &p) override;
};
