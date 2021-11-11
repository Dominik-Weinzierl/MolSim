#include "Gravitation.h"
#include <utils/ArrayUtils.h>
#include "physics/Vector/Vector.h"
#include "spdlog/spdlog.h"

void Gravitation::calculateF(ParticleContainer &particleContainer) const {
  // SPDLOG_INFO("started calculating forces");
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(0, 0, 0);
  }
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      // SPDLOG_DEBUG("Calculating force for {} and {}", i, j);
      double x;
      double y;
      double z;
      double m = i->getM() * j->getM();

      Vector difference = j->getX() - i->getX();
      double l2Norm = ArrayUtils::L2Norm(difference);

      double factor = m / l2Norm;

      x = factor * difference[0];
      y = factor * difference[1];
      z = factor * difference[2];

      i->updateForce(x, y, z);
      j->updateForce(-x, -y, -z);
    }
  }
  // SPDLOG_INFO("ended calculating forces");
}
