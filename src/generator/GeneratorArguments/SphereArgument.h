#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

class SphereArgument : public GeneratorArguments {
 public:
  Vector<> centerCoordinates;
  int radius;
  Vector<> initialVelocity;
  double distance;
  double mass;
  double meanValue;

  SphereArgument(Vector<> pCenterCoordinates, int pRadius, Vector<> pInitialVelocity, double pDistance, double pMass,
                 double pMeanValue = 0.1);
};
