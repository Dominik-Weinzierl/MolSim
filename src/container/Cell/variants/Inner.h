#pragma once

#include "container/Cell/Cell.h"

template<size_t dim>
class Inner : public Cell<dim>{
  void applyCellProperties() override{ }
};
