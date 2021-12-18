#pragma once

#include "container/Cell/Cell.h"

/**
 * Inner is our default Cell which stores only Particle(s).
 * @tparam dim dimension for the simulation
 */
template<size_t dim>
class Inner : public Cell<dim> {
 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * Constructor to create our Inner(s) cells. In this case our boundary type is always Outflow (unused).
   * @param pPosition position of this Cell in our Mesh
   * @param pAllParticles all Particle(s) used in this simulation
   * @param pCellSize size of this cell (each Cell has the same size)
   * @param pDomain domain size used during this simulation
   */
  Inner(std::vector<Particle<dim>> &pAllParticles, Vector<dim> pPosition, Vector<dim> pCellSize, Vector<dim> pDomain)
      : Cell<dim>(pAllParticles, pPosition, pCellSize, pDomain) {};

  //----------------------------------------Methods----------------------------------------

  /**
   * There is no additional behaviour needed.
   */
  inline void applyCellProperties() override {
    SPDLOG_TRACE("Inner[{}]->applyCellProperties()", ArrayUtils::to_string(this->position));
  }
};
