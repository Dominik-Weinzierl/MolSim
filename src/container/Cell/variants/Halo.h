#pragma once

#include "particles/Particle.h"
#include "container/Cell/Cell.h"

/**
 * Halo is a special kind of a Cell which supports the deletion of Particle(s).
 * @tparam dim dimension for the simulation
 */
template<size_t dim>
class Halo : public Cell<dim> {
 public:
  /**
   * Constructor to create our Halo(s).
   * @param pBoundaryType default is Outflow (but other types are also possible)
   * @param pBorderDirection direct of this cell
   * @param pAllParticles all Particle(s) used in this simulation
   * @param pPosition position of this Cell in our Mesh
   * @param pCellSize size of this cell (each Cell has the same size)
   */
  Halo(std::vector<BoundaryType> pBoundaryType, std::vector<BoardDirectionType> pBorderDirection,
       std::vector<Particle<dim>> &pAllParticles, std::array<int, dim> pPosition, std::array<int, dim> pCellSize)
      : Cell<dim>(pBoundaryType, pBorderDirection, pAllParticles, pPosition, pCellSize) {};

  /**
   * Used to set the type of the Particle(s) to -1. This means, that these Particle(s) will be removed soon.
   */
  void applyCellProperties() override {
    SPDLOG_TRACE("Halo[{}]->applyCellProperties()", ArrayUtils::to_string(this->position));
    if (!this->getParticles().empty()) {
      if (this->boundaryType[0] == BoundaryType::Outflow) {
        for (Particle<dim> *p: this->particles) {
          p->setType(-1);
        }
      }
    }
  }
};