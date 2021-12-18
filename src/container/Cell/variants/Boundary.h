#pragma once

#include <cmath>

#include "physics/variants/LennardJones.h"
#include "container/Cell/Cell.h"
#include "particles/Particle.h"
#include "physics/Physics.h"

/**
 * Boundary is a special kind of a Cell which supports the reflection of Particle(s).
 * @tparam dim dimension for the simulation
 */
template<size_t dim>
class Boundary : public Cell<dim> {
 private:
  /**
   * Used to perform correct reflection. Minimum required distance factor.
   */
  const double sixthSqrtOfTwo = std::pow(2, 1.0 / 6.0);

  //----------------------------------------Methods----------------------------------------

  /**
   * Apply the additional force on only the relevant Particle.
   * @param p relevant Particle which will be reflected
   * @param ghost used to perform reflection
   */
  inline void applyForce(Particle<dim> &p, Particle<dim> &ghost) {
    SPDLOG_TRACE("Boundary->applyForce(): {} | {}", p.toString(), ghost.toString());
    double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(p, ghost);
    Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(p, ghost, l2Norm)};
    p.updateForce(force);
  }

  /**
   * Apply smooth reflection.
   * @param p pointer to Particle on which we apply the smooth reflection
   * @param t direction on which we apply this reflection
   */
  inline void applyReflecting(Particle<dim> *p, BoardDirectionType t) {
    SPDLOG_TRACE("Boundary->applyReflecting(): {} | {}", p->toString(), t);
    Particle<dim> ghost{*p};
    double dist;

    size_t index = t / 2;
    // RIGHT, TOP, BACK
    if (t % 2 == 0) {
      dist = (this->position[index] + this->cellSize[index]) - (p->getX()[index]);
    }
      // LEFT, BOTTOM, FRONT
    else {
      dist = -(p->getX()[index] - this->position[index]);
    }

    if (std::fabs(dist) < sixthSqrtOfTwo * p->getZeroCrossing()) {
      auto pos = ghost.getX();
      pos[index] += dist;
      ghost.setX(pos);
      applyForce(*p, ghost);
    }
  }

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * Constructor to create our Boundary(s).
   * @param pBoundaryType default is Outflow (but other types are also possible)
   * @param pBorderDirection direct of this cell
   * @param pAllParticles all Particle(s) used in this simulation
   * @param pPosition position of this Cell in our Mesh
   * @param pCellSize size of this cell (each Cell has the same size)
   * @param pDomain domain size used during this simulation
   */
  Boundary(std::vector<BoundaryType> pBoundaryType, std::vector<BoardDirectionType> pBorderDirection,
           std::vector<Particle<dim>> &pAllParticles, Vector<dim> pPosition, Vector<dim> pCellSize, Vector<dim> pDomain)
      : Cell<dim>(pBoundaryType, pBorderDirection, pAllParticles, pPosition, pCellSize, pDomain) {};

  //----------------------------------------Methods----------------------------------------

  /**
   * Apply selected boundary properties.
   */
  void applyCellProperties() override {
    SPDLOG_TRACE("Boundary[{}]->applyCellProperties()", ArrayUtils::to_string(this->position));
    if (!this->particles.empty()) {
      for (size_t i = 0; i < this->boundaryType.size(); ++i) {
        if (this->boundaryType[i] != BoundaryType::Outflow) {
          for (Particle<dim> *p: this->particles) {
            if (this->boundaryType[i] == BoundaryType::Reflecting) {
              applyReflecting(p, this->borderDirection[i]);
            }
          }
        }
      }
    }
  }
};
