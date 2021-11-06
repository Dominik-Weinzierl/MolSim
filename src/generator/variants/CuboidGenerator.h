#pragma once

#include "generator/Generator.h"

class CuboidGenerator : public Generator {

 private:
  CuboidGenerator() = default;

 public:

  void generate(GeneratorArguments& g, ParticleContainer& p) override;
  void applyMotion(double meanValue, Particle& p) override;
};


