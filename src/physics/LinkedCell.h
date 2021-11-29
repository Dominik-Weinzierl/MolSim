#pragma once

#include "Physics.h"
#include "physics/variants/LennardJones.h"

template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class LinkedCell : public Physics<T, dim> {
  void performUpdate(ParticleContainer<dim> &particleContainer) const override;
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT) const override;
};

template<size_t dim>
class LinkedCell<LennardJones, dim> : public Physics<LennardJones, dim> {
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

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
  */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT) const override {
    // calculate new x
    Physics<LennardJones, dim>::calculateX(particleContainer, deltaT);
    // calculate new f
    Physics<LennardJones, dim>::calculateF(particleContainer);
    // calculate new v
    Physics<LennardJones, dim>::calculateV(particleContainer, deltaT);
  }
};