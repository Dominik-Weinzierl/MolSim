#include "LennardJones.h"

template<>
void LennardJones<3>::performUpdate(ParticleContainer<3> &particleContainer) const {
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());

      Vector<3> force{i->getX() - j->getX()};
      double factor = calculateFactor(force);

      force[0] *= -factor;
      force[1] *= -factor;
      force[2] *= -factor;

      i->updateForce(force[0], force[1], force[2]);
      j->updateForce(-force[0], -force[1], -force[2]);
    }
  }
}

template<>
void LennardJones<2>::performUpdate(ParticleContainer<2> &particleContainer) const {
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());

      Vector<2> force{i->getX() - j->getX()};
      double factor = calculateFactor(force);

      force[0] *= -factor;
      force[1] *= -factor;

      i->updateForce(force[0], force[1]);
      j->updateForce(-force[0], -force[1]);
    }
  }
}

