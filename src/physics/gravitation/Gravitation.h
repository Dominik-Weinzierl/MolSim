#pragma once

#include "physics/Physics.h"

class Gravitation : public Physics {
 public:
  void calculateF(ParticleContainer &particleContainer) const override;
  void calculateX(ParticleContainer &particleContainer, double deltaT) const override;
  void calculateV(ParticleContainer &particleContainer, double deltaT) const override;
};
