#pragma once

#include "container/Cell/Cell.h"

template<size_t dim>
class Inner : public Cell<dim> {
 public:
  Inner(std::array<int, dim> pPosition, std::array<int, dim> pCellSize) : Cell<dim>(pPosition, pCellSize) {};
  void applyCellProperties() override {}
};
