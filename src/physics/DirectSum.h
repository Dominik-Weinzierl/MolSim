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

        Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*i, *j)};

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
    for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
      for (auto j = i + 1; j != particleContainer.end(); ++j) {
        SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());

        Vector<dim> force{Gravitation::calculateForceBetweenTwoParticles<dim>(*i, *j)};

        i->updateForce(force);
        j->updateForce(-force);
      }
    }
  }
};


