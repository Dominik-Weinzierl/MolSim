#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

class CuboidArgument : public GeneratorArguments {
 public:
  Vector<> startingCoordinates;
  std::vector<int> dimensions;
  Vector<> initialVelocity;
  double distance;
  double mass;
  double meanValue;

  CuboidArgument(Vector<> startingCoordinatesIn,
                 std::vector<int> dimensionsIn,
                 Vector<> initialVelocityIn,
                 double distanceIn,
                 double massIn,
                 double meanValueIn = 0.1);
};
