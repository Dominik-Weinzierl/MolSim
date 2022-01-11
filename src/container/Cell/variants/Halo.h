#pragma once

#include "particles/Particle.h"
#include "container/Cell/Cell.h"

/**
 * Halo is a special kind of a Cell which supports the deletion of Particle(s).
 * @tparam dim dimension for the simulation
 */
template<size_t dim>
class Halo : public Cell<dim> {
 private:

  //----------------------------------------Methods----------------------------------------

  /**
   * Move Particle(s) in another Cell.
   */
  inline void moveParticles() {
    Cell<dim> *neighbour = this->getNeighbours()[0];
    for (Particle<dim> *particle: this->getParticles()) {
      const Vector<dim> pos = particle->getX();
      Vector<dim> newPos;
      for (size_t i = 0; i < dim; ++i) {
        newPos[i] = pos[i] - this->getPosition()[i] + neighbour->getPosition()[i];
      }
      particle->setX(newPos);
      neighbour->insertParticle(particle);
    }
    this->particles.clear();
  }
 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * Constructor to create our Halo(s).
   * @param pBoundaryType default is Outflow (but other types are also possible)
   * @param pBorderDirection direct of this cell
   * @param pPosition position of this Cell in our Mesh
   * @param pCellSize size of this cell (each Cell has the same size)
   * @param pDomain domain size used during this simulation
   */
  Halo(std::vector<BoundaryType> pBoundaryType, std::vector<BoardDirectionType> pBorderDirection, Vector<dim> pPosition, Vector<dim> pCellSize, Vector<dim> pDomain)
      : Cell<dim>(pBoundaryType, pBorderDirection, pPosition, pCellSize, pDomain) {};

  //----------------------------------------Methods----------------------------------------

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
      } else if (this->boundaryType[0] == BoundaryType::Periodic) {
        moveParticles();
      }
    }
  }
};


