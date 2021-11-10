#pragma once

#include "physics/Vector/Vector.h"
#include "particles/ParticleContainer.h"
#include "physics/Physics.h"

class LennardJones : public Physics {
 private:
  [[nodiscard]] static Vector getF(const Vector& position1, const Vector& position2, double zeroCrossing, double potentialWellDepth);
 public:
  void calculateF(ParticleContainer &particleContainer) const override;
};
