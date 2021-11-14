#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

template<size_t dim>
class CuboidArgument : public GeneratorArguments {
 public:
  Vector<dim> startingCoordinates;
  std::vector<int> dimensions;
  Vector<dim> initialVelocity;
  double distance;
  double mass;
  double meanValue;

  CuboidArgument(Vector<dim> pStartingCoordinates, std::vector<int> pDimensions, Vector<dim> pInitialVelocity,
                 double pDistance, double pMass, double pMeanValue = 0.1) : startingCoordinates{pStartingCoordinates},
                                                                            dimensions{std::move(pDimensions)},
                                                                            initialVelocity{pInitialVelocity},
                                                                            distance{pDistance}, mass{pMass},
                                                                            meanValue{pMeanValue} {

  }
};
