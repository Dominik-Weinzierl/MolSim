#pragma once

#include "container/Cell/Cell.h"

/**
 * Inner is our default Cell which stores only Particle(s).
 * @tparam dim dimension for the simulation
 */
template<size_t dim>
class Inner : public Cell<dim> {
 public:
  /**
   * Constructor to create our Inner(s) cells. In this case our boundary type is always Outflow (unused).
   * @param pPosition position of this Cell in our Mesh
   * @param pAllParticles all Particle(s) used in this simulation
   * @param pCellSize size of this cell (each Cell has the same size)
   */
  Inner(std::vector<Particle<dim>> &pAllParticles, std::array<int, dim> pPosition, std::array<int, dim> pCellSize)
      : Cell<dim>(pAllParticles, pPosition, pCellSize) {};

  /**
   * There is no additional behaviour needed.
   */
  inline void applyCellProperties() override {}
};
