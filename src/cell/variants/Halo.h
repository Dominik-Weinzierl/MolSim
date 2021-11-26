#pragma once

#include "particles/Particle.h"
#include "cell/Cell.h"
#include "boundaryConditions/variants/Outflow.h"

template<typename T, size_t dim, typename std::enable_if<std::is_base_of<BoundaryConditions, T>::value,
                                             bool>::type = true>
class Halo : public Cell<T, dim>{
  void applyCellProperties(T& t) override { }
};

template<>
void Halo<Outflow, 2>::applyCellProperties(Outflow &o) {
  particles.clear();
}

template<>
void Halo<Outflow, 3>::applyCellProperties(Outflow &o) {
  particles.clear();
}