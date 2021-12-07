#pragma once

#include "Physics.h"
#include "physics/variants/LennardJones.h"
#include "physics/variants/Gravitation.h"

/**
 * This class implements the DirectSum-algorithm.
 * @tparam T The physics to be used.
 * @tparam dim The dimension of the simulation.
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class DirectSum : public Physics<T, dim> {
 public:
  void performUpdate(ParticleContainer<dim> &particleContainer) const override;
};

/**
 * Implements DirectSum algorithm for LennardJones
 * @tparam dim The dimension of our simulation
 */
template<size_t dim>
class DirectSum<LennardJones, dim> : public Physics<LennardJones, dim> {
 public:
  void performUpdate(ParticleContainer<dim> &particleContainer) const override {
    for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
      for (auto j = i + 1; j != particleContainer.end(); ++j) {
        SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());

        double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*i, *j);
        Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*i, *j, l2Norm)};

        i->updateForce(force);
        j->updateForce(-force);
      }
    }
  }
};

/**
 * Implements DirectSum for Gravitation
 * @tparam dim The dimension of our simulation
 */
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


