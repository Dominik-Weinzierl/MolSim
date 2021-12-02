#pragma once

#include "particles/Particle.h"
#include "container/Cell/Cell.h"

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

  void applyCellProperties() override {
    if (!this->particles.empty()) {
      if (all_of(this->boundaryType.begin(), this->boundaryType.end(), [&](int i) {
        return i == BoundaryType::Outflow;
      })) {
        for (auto *p: this->particles) {
          this->allParticles
              .erase(std::remove(this->allParticles.begin(), this->allParticles.end(), *p), this->allParticles.end());
        }
      } else {
        // TODO: NEED TO HANDLE OTHER CASES
      }
    }
  }
};