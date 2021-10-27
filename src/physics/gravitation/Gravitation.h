#pragma once

#include "physics/Physics.h"

class Gravitation : public Physics {
 public:
  void calculateF(const ParticleContainer &particleContainer) override;
  void calculateX(const ParticleContainer &particleContainer) override;
  void calculateV(const ParticleContainer &particleContainer) override;
};
