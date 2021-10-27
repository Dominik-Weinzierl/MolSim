#pragma once

#include "physics/Physics.h"

class Gravitation : public Physics{

  void calculateF(const ParticleContainer &particleContainer) override;
};
