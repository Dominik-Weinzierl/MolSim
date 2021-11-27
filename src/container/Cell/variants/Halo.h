#pragma once

#include "particles/Particle.h"
#include "boundaryConditions/variants/Outflow.h"
#include "container/Cell/Cell.h"

template<typename T, size_t dim, typename std::enable_if<std::is_base_of<BoundaryCondition, T>::value,
                                                         bool>::type = true>
class Halo : public Cell<T, dim> {
  void applyCellProperties(T &t) override {}
};

template<size_t dim>
void Halo<Outflow, dim>::applyCellProperties(Outflow &o) {
  particles.clear();
}