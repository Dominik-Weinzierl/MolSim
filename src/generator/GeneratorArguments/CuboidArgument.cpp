#include "CuboidArgument.h"

#include <utility>

CuboidArgument::CuboidArgument(Vector<> startingCoordinatesIn, std::vector<int> dimensionsIn,
                               Vector<> initialVelocityIn, double distanceIn, double massIn, double meanValueIn)
    : startingCoordinates{startingCoordinatesIn},
      dimensions{std::move(dimensionsIn)},
      initialVelocity{initialVelocityIn},
      distance{distanceIn},
      mass{massIn},
      meanValue{meanValueIn} {

}
