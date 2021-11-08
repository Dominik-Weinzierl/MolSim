#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

 struct CuboidArgument : public GeneratorArguments {
   Vector startingCoordinates;
   Vector dimensions;
   Vector initialVelocity;
   double distance;
   double mass;
   double meanValue = 0.1; //TODO: We'll may change this value when we test the simulation
 };
