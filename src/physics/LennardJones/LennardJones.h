#pragma once

#include "physics/Vector/Vector.h"
#include "particles/ParticleContainer.h"
#include "physics/Physics.h"

class LennardJones : public Physics {
 private:
  static void updateF(Vector<> &diff, double zeroCrossing, double potentialWellDepth) ;
 public:
  void calculateF(ParticleContainer &particleContainer) const override;
};
