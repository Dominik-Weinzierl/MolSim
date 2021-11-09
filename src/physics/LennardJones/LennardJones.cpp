#include "LennardJones.h"
#include <utils/ArrayUtils.h>

Vector LennardJones::getForce(const Vector &position1, const Vector &position2, double zeroCrossing,
                              double potentialWellDepth) {

  l2Norm = ArrayUtils::L2Norm(position1 - position2);
  auto fracture = zeroCrossing / l2Norm;

  auto firstFactor = (24 * potentialWellDepth) / (std::pow(l2Norm, 2));
  auto secondFactor = std::pow(fracture, 6) - 2 * std::pow(fracture, 12);
  auto thirdFactor = position2 - position1;
  auto force = firstFactor * secondFactor * thirdFactor;

  return -force;
}
