#pragma once

#include "container/ParticleContainer.h"

/**
 * This is the superclass for the different types of physics we implemented.
 */
class PhysicsType {
};

/**
 * Physics is an abstract class which provides methods to calculate the next simulation step
 * based on the template method pattern.
 *
 *
 * @tparam dim dimension of our simulation.
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of_v<PhysicsType, T>, bool>::type = true>
class Physics {

 protected:

  //----------------------------------------Constructor & Destructor----------------------------------------

  /**
   * Default destructor.
   */
  virtual ~Physics() = default;

  //----------------------------------------Methods----------------------------------------

  /**
   * Updates the force of the Particle(s).
   * @param particleContainer container which contains the Particle(s) used for this simulation.
   */
  virtual void performUpdate(ParticleContainer<dim> &particleContainer) const = 0;

 public:
  /**
   * Calculates and updates the position of all particles in the specified container.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
   */
  static void calculateX(ParticleContainer<dim> &particleContainer, double deltaT) {
    SPDLOG_DEBUG("started calculating positions");
    const auto deltaTPow = deltaT * deltaT;
    Vector<dim> temp{};

//#pragma omp parallel for shared(particleContainer, deltaT, deltaTPow, std::cout) private(temp) default(none)
    for (size_t t = 0; t < particleContainer.size(); ++t) {
      Particle<dim> &p = particleContainer.getParticles()[t];
      SPDLOG_TRACE("Calculating position for {}", p.toString());
      for (size_t i = 0; i < dim; ++i) {
        temp[i] = p.getX()[i] + deltaT * p.getV()[i] + deltaTPow * (p.getF()[i] / (2 * p.getM()));
      }
      p.setX(temp);
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
    Vector<dim> temp{};
//#pragma omp parallel for shared(particleContainer, deltaT) private(temp) default(none)
    for (size_t t = 0; t < particleContainer.size(); ++t) {
      Particle<dim> &p = particleContainer.getParticles()[t];
      SPDLOG_TRACE("Calculating velocity for {}", p.toString());
      for (size_t i = 0; i < dim; ++i) {
        temp[i] = p.getV()[i] + deltaT * (p.getOldF()[i] + p.getF()[i]) / (2 * p.getM());
      }
      p.setV(temp);
    }
    SPDLOG_DEBUG("ended calculating velocities");
  }

  /**
   * Calculates and updates the force for all particles in the specified container
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param gravitation Vector that contains the additional gravitation force
   */
  void calculateF(ParticleContainer<dim> &particleContainer, Vector<dim> &gravitation, double current_time) const {
    SPDLOG_DEBUG("started calculating forces");
//#pragma omp parallel for shared(particleContainer, additionalForce) default(none)
    for (size_t t = 0; t < particleContainer.size(); ++t) {
      Particle<dim> &p = particleContainer.getParticles()[t];
      p.setOldF(p.getF());
      p.setF(p.getM() * gravitation);

      for (const Force<dim> &force: p.getAdditionalForces()) {
        if (force.getStartTime() <= current_time && force.getEndTime() > current_time) {
          p.updateForce(force.getForce());
        }
      }
    }

    performUpdate(particleContainer);
    SPDLOG_DEBUG("ended calculating forces");
  }

  /**
  * Calls the calculate-Methods for the position, force and velocity with the given parameters.
  * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
  * @param deltaT time step of our simulation
  * @param gravitation Vector that contains the additional gravitation force
  */
  virtual void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, Vector<dim> &gravitation,
                                 double current_time) const {
    // calculate new x
    calculateX(particleContainer, deltaT);
    // calculate new f
    calculateF(particleContainer, gravitation, current_time);
    // calculate new v
    calculateV(particleContainer, deltaT);
  }

  //----------------------------------------Helper----------------------------------------

  /**
   * Calculates the square of the l2Norm for two given Particles.
   * @param i Particle one
   * @param j Particle two
   * @return Square of l2Norm
   */
  static inline double calcL2NormSquare(Particle<dim> &i, Particle<dim> &j) {
    double l2Norm = 0.0;
    for (size_t t = 0; t < dim; ++t) {
      double diff = i.getX()[t] - j.getX()[t];
      l2Norm += diff * diff;
    }
    return l2Norm;
  }
};
