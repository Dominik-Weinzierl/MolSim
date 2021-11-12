#include "LennardJones.h"
#include <utils/ArrayUtils.h>
#include "spdlog/spdlog.h"

void LennardJones::updateF(Vector<> &diff, double zeroCrossing, double potentialWellDepth) {
  double l2Norm = ArrayUtils::L2Norm(diff);
  double fracture = zeroCrossing / l2Norm;

  double firstFactor = (24 * potentialWellDepth) / (l2Norm * l2Norm);
  double pow = fracture * fracture * fracture * fracture * fracture * fracture;
  double secondFactor = pow - 2 * pow * pow;
  double factor = firstFactor * secondFactor;

  diff[0] *= -factor;
  diff[1] *= -factor;
  diff[2] *= -factor;
}

void LennardJones::calculateF(ParticleContainer &particleContainer) const {
  SPDLOG_INFO("started calculating forces");
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(0, 0, 0);
  }
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      SPDLOG_DEBUG("Calculating force for {} and {}", i, j);

      //TODO: Outsource zeroCrossing and potentialWellDepth to Particles
      Vector<> force{i->getX() - j->getX()};
      updateF(force, 1, 5);

      i->updateForce(force[0], force[1], force[2]);
      j->updateForce(-force[0], -force[1], -force[2]);
    }
  }
  SPDLOG_INFO("ended calculating forces");
}
