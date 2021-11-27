#pragma once

#include "container/ParticleContainer.h"
#include "container/Cell/Cell.h"
#include <vector>

/**
 * LinkedCell is a container used to perform calculations based on the linked cell algorithm.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class LinkedCellContainer : public ParticleContainer<dim> {
 private:
  std::vector<Cell<BoundaryCondition, dim>> cells;
  Vector<dim> cellSize;
  Vector<dim> dimension;

  int getIndexBasedOnCoordinates([[maybe_unused]] Vector<dim> coords) {}

 public:
  LinkedCellContainer() = default;

  /**
   * Constructs a LinkedCell from the provided vector of particles.
   * @param pParticles vector of particles as initial value.
   */
  LinkedCellContainer(std::vector<Particle<dim>> pParticles, Vector<dim> pCellSize, Vector<dim> pDimension)
      : ParticleContainer<dim>(pParticles), dimension{pDimension}, cellSize{pCellSize} {
    SPDLOG_TRACE("LinkedCell generated");
  }

  /**
   * Constructs a LinkedCell from the provided vector of particles.
   * @param pParticles vector of particles as initial value.
   */
  LinkedCellContainer(Vector<dim> pCellSize, Vector<dim> pDimension) : dimension{pDimension}, cellSize{pCellSize} {
    SPDLOG_TRACE("LinkedCell generated");
  }

  void insertParticlesInCells() {
    for (Particle<dim> &p: ParticleContainer<dim>::particles) {
      Cell<BoundaryCondition, dim> &cell = cells[getIndexBasedOnCoordinates(p.getX())];
      cell.insertParticle(p);
    }
  }
};