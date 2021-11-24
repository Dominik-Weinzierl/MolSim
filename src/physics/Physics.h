#pragma once

#include "particles/ParticleContainer.h"

/**
 * Physics is an abstract class which provides methods to calculate the next simulation step
 * based on the template method pattern.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class Physics {
 protected:
  /**
   * Default destructor.
   */
  virtual ~Physics() = default;

  /**
   * Calculates and updates the force for all particles in the specified container
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   */
  virtual void calculateF(ParticleContainer<dim> &particleContainer) const = 0;

 public:
  /**
   * Calculates and updates the position of all particles in the specified container.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
   */
  static void calculateX(ParticleContainer<dim> &particleContainer, double deltaT) {
    SPDLOG_DEBUG("started calculating positions");
    const auto deltaTPow = deltaT * deltaT;
    std::array<double, dim> temp{};

    for (auto &p: particleContainer) {
      SPDLOG_TRACE("Calculating position for {}", p.toString());
      for (size_t i = 0; i < dim; ++i) {
        temp[i] = p.getX()[i] + deltaT * p.getV()[i] + deltaTPow * (p.getF()[i] / (2 * p.getM()));
      }
      p.setV(temp);
    }
    SPDLOG_DEBUG("ended calculating positions");
  }

  /**
   * Calculates and updates the velocity of all particles in the specified container.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
   */
  static void calculateV(ParticleContainer<dim> &particleContainer, double deltaT) {
    SPDLOG_DEBUG("started calculating velocities");
    std::array<double, dim> temp{};
    for (auto &p: particleContainer) {
      SPDLOG_TRACE("Calculating velocity for {}", p.toString());
      for (size_t i = 0; i < dim; ++i) {
        temp[i] = p.getV()[i] + deltaT * (p.getOldF()[i] + p.getF()[i]) / (2 * p.getM());
      }
      p.setV(temp);
    }
    SPDLOG_DEBUG("ended calculating velocities");
  }

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
   */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT) const {
    // calculate new x
    calculateX(particleContainer, deltaT);
    // calculate new f
    calculateF(particleContainer);
    // calculate new v
    calculateV(particleContainer, deltaT);
  }
};

