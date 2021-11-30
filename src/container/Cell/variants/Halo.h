#pragma once

#include "particles/Particle.h"
#include "container/Cell/Cell.h"

template<size_t dim>
class Halo : public Cell<dim> {
 public:
  Halo(BoundaryType pBoundaryType, std::array<int, dim> pPosition, std::array<int, dim> pCellSize) : Cell<dim>(
      pBoundaryType, pPosition, pCellSize) {};
  void applyCellProperties() override {
    Vector<dim> temp{};
    for (Particle<dim> *p: this->particles) {
      // Don't move anymore
      p->setV(temp);
    }
  }
};