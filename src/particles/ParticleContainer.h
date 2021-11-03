#pragma once

#include "Particle.h"
#include <vector>

//! ParticleContainer is a container for particles that provides functions to iterate over single particles and pairs.
class ParticleContainer {
 private:
  std::vector<Particle> particles;

 public:
  ParticleContainer();
  virtual ~ParticleContainer();

  //! Constructs a ParticleContainer from the provided vector of particles
  //! \param particles
  explicit ParticleContainer(std::vector<Particle> particles);
  ParticleContainer(const ParticleContainer &particleContainer) = default;

  //! Adds the particle to the ParticleContainer
  //! \param p the particle to be added
  void addParticle(const Particle &p);

  [[nodiscard]] std::vector<Particle> &getParticles();

  [[nodiscard]] unsigned long size() const;

  [[nodiscard]] auto begin() { return particles.begin(); }
  [[nodiscard]] auto end() { return particles.end(); }
};