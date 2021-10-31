#pragma once

#include "Particle.h"
#include <list>

//! a container for particles that provides functions to iterate over single particles and a list of (unique) pairs.
class ParticleContainer {
 private:
  std::list<Particle> particles;
  std::list<std::pair<Particle &, Particle &>> particlePairs;

  void addParticleToPairs(Particle &p);

 public:
  ParticleContainer();
  virtual ~ParticleContainer();

  //! Constructs a ParticleContainer from the provided list of particles
  //! \param particles

  explicit ParticleContainer(std::list<Particle> particles);

  //! Adds the particle to the ParticleContainer
  //! \param p the particle to be added
  void addParticle(const Particle &p);

  [[nodiscard]] std::list<Particle> &getParticles();
  [[nodiscard]] std::list<std::pair<Particle &, Particle &>> &getParticlePairs();

  [[nodiscard]] int size() const;
};