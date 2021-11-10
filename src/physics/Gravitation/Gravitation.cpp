#include "Gravitation.h"
#include <cmath>
#include <iostream>
#include <utils/ArrayUtils.h>
#include "physics/Vector/Vector.h"
#include "spdlog/spdlog.h"

void Gravitation::calculateF(ParticleContainer &particleContainer) const {
  SPDLOG_INFO("started calculating forces");
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(Physics::ZERO);
  }
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      SPDLOG_DEBUG("Calculating force for {} and {}", i, j);
      const auto difference = j->getX() - i->getX();
      Vector force = difference;
      const auto l2Norm = ArrayUtils::L2Norm(difference);
      force *= i->getM() * j->getM();
      force /= std::pow(l2Norm, 3);

      i->updateForce(force);
      j->updateForce(-force);
    }
  }
  SPDLOG_INFO("ended calculating forces");
}
