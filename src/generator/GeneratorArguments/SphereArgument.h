#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

template<size_t dim>
class SphereArgument : public GeneratorArguments {
 public:
  Vector<dim> centerCoordinates;
  int radius;
  Vector<dim> initialVelocity;
  double distance;
  double mass;
  double meanValue;

  SphereArgument(Vector<dim> pCenterCoordinates, int pRadius, Vector<dim> pInitialVelocity, double pDistance,
                 double pMass, double pMeanValue = 0.1) : centerCoordinates{pCenterCoordinates}, radius{pRadius},
                                                          initialVelocity{pInitialVelocity}, distance{pDistance},
                                                          mass{pMass}, meanValue{pMeanValue} {
  }

};
