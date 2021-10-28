#pragma once

#include "physics/Physics.h"

class Gravitation : public Physics {
 public:
  void calculateF(const ParticleContainer &particleContainer) const override;
  void calculateX(const ParticleContainer &particleContainer, double deltaT) const override;
  void calculateV(const ParticleContainer &particleContainer, double deltaT) const override;
};
