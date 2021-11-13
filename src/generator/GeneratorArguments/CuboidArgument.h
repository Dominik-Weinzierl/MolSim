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

  CuboidArgument(Vector<> pStartingCoordinates, std::vector<int> pDimensions, Vector<> pInitialVelocity,
                 double pDistance, double pMass, double pMeanValue = 0.1);
};
