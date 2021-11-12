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

  CuboidArgument(Vector<> startingCoordinates, std::vector<int> dimensions, Vector<> initialVelocity, double distance, double mass,
                 double meanValue = 0.1);
};
