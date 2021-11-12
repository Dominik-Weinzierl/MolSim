#include "CuboidArgument.h"

#include <utility>

CuboidArgument::CuboidArgument(Vector<> startingCoordinates, std::vector<int> dimensions,
                               Vector<> initialVelocity, double distance, double mass, double meanValue)
    : startingCoordinates{startingCoordinates}, dimensions{std::move(dimensions)}, initialVelocity{initialVelocity},
      distance{distance}, mass{mass}, meanValue{meanValue} {

}
