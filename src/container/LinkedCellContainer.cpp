#include "LinkedCellContainer.h"

template<>
int LinkedCellContainer<2>::getIndexBasedOnCoordinates(Vector<2> coords) {
  return 0;
}

template<>
int LinkedCellContainer<3>::getIndexBasedOnCoordinates(Vector<3> coords) {
  return 0;
}

