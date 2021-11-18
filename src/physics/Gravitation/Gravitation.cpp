#include "Gravitation.h"

template<>
void Gravitation<3>::performUpdate(ParticleContainer<3> &particleContainer) const {
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());
      double x;
      double y;
      double z;
      double m = i->getM() * j->getM();

      Vector<3> difference = j->getX() - i->getX();
      double l2Norm = ArrayUtils::L2Norm(difference);

      double factor = m / (l2Norm * l2Norm * l2Norm);

      x = factor * difference[0];
      y = factor * difference[1];
      z = factor * difference[2];

      i->updateForce(x, y, z);
      j->updateForce(-x, -y, -z);
    }
  }
}

template<>
void Gravitation<2>::performUpdate(ParticleContainer<2> &particleContainer) const {
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());
      double x;
      double y;
      double m = i->getM() * j->getM();

      // Since 2D calculations for gravitation are wrong, we need to wrap with 3D.
      Vector<3> difference{j->getX()[0] - i->getX()[0], j->getX()[1] - i->getX()[1], 0};
      double l2Norm = ArrayUtils::L2Norm(difference);

      double factor = m / (l2Norm * l2Norm * l2Norm);

      x = factor * difference[0];
      y = factor * difference[1];

      i->updateForce(x, y);
      j->updateForce(-x, -y);
    }
  }
}

template<>
void Gravitation<2>::calculateF(ParticleContainer<2> &particleContainer) const {
  SPDLOG_DEBUG("started calculating forces");
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(0, 0);
  }
  performUpdate(particleContainer);
  SPDLOG_DEBUG("ended calculating forces");
}

template<>
void Gravitation<3>::calculateF(ParticleContainer<3> &particleContainer) const {
  SPDLOG_DEBUG("started calculating forces");
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(0, 0, 0);
  }
  performUpdate(particleContainer);
  SPDLOG_DEBUG("ended calculating forces");
}

