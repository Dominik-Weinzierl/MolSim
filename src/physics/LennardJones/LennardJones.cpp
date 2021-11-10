#include "LennardJones.h"
#include <utils/ArrayUtils.h>
#include "spdlog/spdlog.h"

Vector LennardJones::getF(const Vector &difference, double zeroCrossing, double potentialWellDepth) {

  double l2Norm = ArrayUtils::L2Norm(difference);
  double fracture = zeroCrossing / l2Norm;

  double firstFactor = (24 * potentialWellDepth) / (l2Norm * l2Norm);
  double pow = fracture * fracture * fracture * fracture * fracture * fracture;
  double secondFactor = pow - 2 * pow * pow;
  //Constructs two Vectors for Vector force = firstFactor * secondFactor * thirdFactor;, now only one
  Vector force = difference;
  force *= firstFactor;
  force *= secondFactor;

  return force;
}

void LennardJones::calculateF(ParticleContainer &particleContainer) const {
  // SPDLOG_INFO("started calculating forces");
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(Physics::ZERO);
  }
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      // SPDLOG_DEBUG("Calculating force for {} and {}", i, j);

      //TODO: Outsource zeroCrossing and potentialWellDepth to Particles
      Vector force = getF(j->getX() - i->getX(), 1, 5);

      i->updateForce(force);
      j->updateForce(-force);
    }
  }
  // SPDLOG_INFO("ended calculating forces");
}
