#include "LennardJones.h"
#include <utils/ArrayUtils.h>
#include "spdlog/spdlog.h"

Vector LennardJones::getF(const Vector &position1, const Vector &position2, double zeroCrossing,
                              double potentialWellDepth) {

  double l2Norm = ArrayUtils::L2Norm(position1 - position2);
  double fracture = zeroCrossing / l2Norm;

  double firstFactor = (24 * potentialWellDepth) / (std::pow(l2Norm, 2));
  double secondFactor = std::pow(fracture, 6) - 2 * std::pow(fracture, 12);
  Vector thirdFactor = position2 - position1;
  //Constructs two Vectors for Vector force = firstFactor * secondFactor * thirdFactor;, now only one
  Vector force = thirdFactor;
  force *= firstFactor;
  force *= secondFactor;

  return -force;
}

void LennardJones::calculateF(ParticleContainer &particleContainer) const {
  SPDLOG_INFO("started calculating forces");
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(Physics::ZERO);
  }
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      SPDLOG_DEBUG("Calculating force for {} and {}", i, j);

      //TODO: Outsource zeroCrossing and potentialWellDepth to Particles
      Vector force = getF(i->getX(), j->getX(), 1, 5);

      i->updateForce(force);
      j->updateForce(-force);
    }
  }
  SPDLOG_INFO("ended calculating forces");
}
