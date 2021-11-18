#include "LennardJones.h"

template<>
inline double LennardJones<3>::calculateFactor(const Vector<3> &diff) const {
  double l2Norm = diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2];
  double fracture = (zeroCrossing * zeroCrossing) / l2Norm;

  double firstFactor = (24 * potentialWellDepth) / (l2Norm);
  double pow = fracture * fracture * fracture;
  double secondFactor = pow - 2 * pow * pow;
  return firstFactor * secondFactor;
}

template<>
inline double LennardJones<2>::calculateFactor(const Vector<2> &diff) const {
  double l2Norm = diff[0] * diff[0] + diff[1] * diff[1];
  double fracture = (zeroCrossing * zeroCrossing) / l2Norm;

  double firstFactor = (24 * potentialWellDepth) / (l2Norm);
  double pow = fracture * fracture * fracture;
  double secondFactor = pow - 2 * pow * pow;
  return firstFactor * secondFactor;
}

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

template<>
void LennardJones<2>::calculateF(ParticleContainer<2> &particleContainer) const {
  SPDLOG_DEBUG("started calculating forces");
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(0, 0);
  }
  performUpdate(particleContainer);
  SPDLOG_DEBUG("ended calculating forces");
}

template<>
void LennardJones<3>::calculateF(ParticleContainer<3> &particleContainer) const {
  SPDLOG_DEBUG("started calculating forces");
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(0, 0, 0);
  }
  performUpdate(particleContainer);
  SPDLOG_DEBUG("ended calculating forces");
}

