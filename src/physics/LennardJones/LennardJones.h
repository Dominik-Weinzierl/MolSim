#pragma once

#include "physics/Vector/Vector.h"
#include "particles/ParticleContainer.h"
#include "physics/Physics.h"
#include <utils/ArrayUtils.h>

template<size_t dim>
class LennardJones : public Physics<dim> {
 private:
  double zeroCrossing = 1;
  double potentialWellDepth = 5;

  [[nodiscard]] inline double calculateFactor(const Vector<dim> &diff) const {
    double l2Norm = ArrayUtils::L2Norm(diff);
    double fracture = zeroCrossing / l2Norm;

    double firstFactor = (24 * potentialWellDepth) / (l2Norm * l2Norm);
    double pow = fracture * fracture * fracture * fracture * fracture * fracture;
    double secondFactor = pow - 2 * pow * pow;
    return firstFactor * secondFactor;
  }

  void performUpdate(ParticleContainer<dim> &particleContainer) const;

 public:
  void calculateF(ParticleContainer<dim> &particleContainer) const override {
    SPDLOG_DEBUG("started calculating forces");
    for (auto &p: particleContainer) {
      p.setOldF(p.getF());
      p.setF(0, 0, 0);
    }
    performUpdate(particleContainer);
    SPDLOG_DEBUG("ended calculating forces");
  }
};

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
