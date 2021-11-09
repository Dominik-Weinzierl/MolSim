#pragma once

#include "physics/Vector/Vector.h"

class LennardJones {
 private:
  double l2Norm;

 public:
  Vector getForce(const Vector& position1, const Vector& position2, double zeroCrossing, double potentialWellDepth);
};