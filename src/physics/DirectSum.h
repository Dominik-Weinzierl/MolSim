#pragma once

#include "Physics.h"
#include "physics/variants/LennardJones.h"
#include "physics/variants/Gravitation.h"

template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class DirectSum : public Physics<T, dim> {
 public:
  void performUpdate(ParticleContainer<dim> &particleContainer) const override;
};

template<size_t dim>
class DirectSum<LennardJones, dim> : public Physics<LennardJones, dim> {
 public:
  void performUpdate(ParticleContainer<dim> &particleContainer) const override {
    for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
      for (auto j = i + 1; j != particleContainer.end(); ++j) {
        SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());

        Vector<dim> force{i->getX() - j->getX()};
        double l2Norm = 0.0;

        for (size_t t = 0; t < dim; ++t) {
          l2Norm += force[t] * force[t];
        }

        double fracture = (this->zeroCrossing * this->zeroCrossing) / l2Norm;

        double firstFactor = (24 * this->potentialWellDepth) / (l2Norm);
        double pow = fracture * fracture * fracture;
        double secondFactor = pow - 2 * pow * pow;
        double factor = firstFactor * secondFactor;

        for (size_t t = 0; t < 2; ++t) {
          force[t] *= -factor;
        }

        i->updateForce(force);
        j->updateForce(-force);
      }
    }
  }
};

template<size_t dim>
class DirectSum<Gravitation, dim> : public Physics<Gravitation, dim> {
 public:
  void performUpdate(ParticleContainer<dim> &particleContainer) const override {
    Vector<dim> temp{};
    for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
      for (auto j = i + 1; j != particleContainer.end(); ++j) {
        SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());
        double m = i->getM() * j->getM();

        Vector<dim> difference = j->getX() - i->getX();
        double l2Norm = ArrayUtils::L2Norm(difference);

        double factor = m / (l2Norm * l2Norm * l2Norm);

        for (size_t t = 0; t < dim; ++t) {
          temp[t] = factor * difference[t];
        }

        i->updateForce(temp);
        j->updateForce(-temp);
      }
    }
  }
};


