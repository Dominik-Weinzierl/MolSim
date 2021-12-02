#pragma once

#include "container/ParticleContainer.h"

/**
 * DirectSum is a container used to perform calculations based on the direct sum algorithm.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class DirectSumContainer : public ParticleContainer<dim> {
 public:
  /**
   * Constructs a DirectSumContainer from the provided vector of particles.
   * @param pParticles vector of particles as initial value.
   */
  explicit DirectSumContainer(std::vector<Particle<dim>> pParticles) : ParticleContainer<dim>(pParticles) {
    SPDLOG_TRACE("DirectSumContainer generated");
  }

  /**
  * Constructs a DirectSumContainer from the provided vector of particles.
   * @param pParticles vector of particles as initial value.
   */
  DirectSumContainer() = default;

  /**
   * There is no additional setup needed for direct sum calculations.
   */
  void init() override {};
};