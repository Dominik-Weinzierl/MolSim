#pragma once

#include "Particle.h"
#include <vector>

//! a container for particles that provides functions to iterate over single particles and a vector of (unique) pairs.
class ParticleContainer {
 private:
  std::vector<Particle> particles;
  std::vector<std::pair<Particle &, Particle &>> particlePairs;

  void addParticleToPairs(Particle &p);

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
  [[nodiscard]] std::vector<std::pair<Particle &, Particle &>> &getParticlePairs();

  [[nodiscard]] unsigned long size() const;
};