#include "CuboidArgument.h"

CuboidArgument::CuboidArgument(Vector startingCoordinates, std::vector<int> dimensions,
                               Vector initialVelocity, double distance, double mass, double meanValue)
    : startingCoordinates{startingCoordinates}, dimensions{dimensions}, initialVelocity{initialVelocity},
      distance{distance}, mass{mass}, meanValue{meanValue} {

}
