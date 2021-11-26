#pragma once

#include "cell/Cell.h"
#include "boundaryConditions/BoundaryCondition.h"

template<typename T, size_t dim, typename std::enable_if<std::is_base_of<BoundaryConditions, T>::value,
                                             bool>::type = true>
class Inner : public Cell<T, dim>{
  static void applyCellProperties(T& t){ }
};
