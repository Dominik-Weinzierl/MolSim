#pragma once

#include "particles/Particle.h"
#include "container/Cell/Cell.h"

template<size_t dim>
class Halo : public Cell<dim> {
 public:
  explicit Halo(BoundaryType pBoundaryType) : Cell<dim>(pBoundaryType) {};
  void applyCellProperties() override {}
};