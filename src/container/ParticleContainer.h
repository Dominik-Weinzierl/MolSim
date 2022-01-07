#pragma once

#include <vector>

#include "particles/Particle.h"
#include "logger/Logger.h"
#include "physics/Forces/ForceContainer.h"

/**
 * ParticleContainer is a container for particles that provides functions to iterate over single particles and pairs.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class ParticleContainer {
 protected:
  /**
   * Particles-Vector Stores all particles.
   */
  std::vector<Particle<dim>> particles;

 public:

  //----------------------------------------Constructor & Destructor----------------------------------------

  /**
   * Default Constructor.
   */
  ParticleContainer() = default;

  /**
   * Default Destructor.
   */
  virtual ~ParticleContainer() = default;

  /**
   * Constructs a ParticleContainer from the provided vector of particlesIn.
   * @param pParticles vector of particles as initial value.
   */
  explicit ParticleContainer(std::vector<Particle<dim>> pParticles) : particles{std::move(pParticles)} {
    SPDLOG_TRACE("ParticleContainer generated");
  }

  //----------------------------------------Methods----------------------------------------

  /**
   * Adds the particle to the ParticleContainer.
   * @param p The particle to be added.
   */
  void addParticle(Particle<dim> p) {
    particles.push_back(std::move(p));
  }

  /**
   * @return Iterator to the beginning of the particles-Vector.
   */
  [[nodiscard]] auto begin() { return particles.begin(); }

  /**
   * @return Iterator to the end of the particles-Vector.
   */
  [[nodiscard]] auto end() { return particles.end(); }

  /**
   * @return Size of the particle-Vector.
   */
  [[nodiscard]] unsigned long size() const {
    return particles.size();
  }

  /**
 * Operator that allows mutable member access.
 * @param i Index for member access.
 * @return Particle<dim> as reference
 */
  Particle<dim> &operator[](unsigned long i) {
    return particles[i];
  }

  /**
   * Operator that allows immutable member access.
   * @param i Index for member access.
   * @return Particle<dim> as value
   */
  Particle<dim> operator[](unsigned long i) const {
    return particles[i];
  }

  /**
   * Setup all additional container or structures used by this container.
   */
  virtual void init() = 0;

  /**
   * Updates the distribution of the particles into the cells
   */
  virtual void updateCells() = 0;

  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * const getter for the vector of Particle(s).
   * @return const std::vector<Particle<dim>>
   */
  [[nodiscard]] const std::vector<Particle<dim>> &getParticles() const {
    return particles;
  }

  /**
   * Getter for the vector of Particle(s).
   * @return std::vector<Particle<dim>>
   */
  [[nodiscard]] std::vector<Particle<dim>> &getParticles() {
    return particles;
  }
};

/**
 * Operator == to compare ParticleContainers for testing
 * @tparam dim Dimension of the Particles in the ParticleContainer
 * @param p1 One of the two ParticleContainers to compare
 * @param p2 One of the two ParticleContainers to compare
 * @return True, if both ParticleContainers are the same
 */
template<size_t dim>
bool operator==(const ParticleContainer<dim> &p1, const ParticleContainer<dim> &p2) {
  return p1.getParticles() == p2.getParticles();
}
