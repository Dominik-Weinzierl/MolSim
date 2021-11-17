#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

/**
 * Arguments used to create Cuboid(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class CuboidArgument : public GeneratorArguments {
 public:
  /**
   * Coordinates of the lower left corner.
   */
  Vector<dim> startingCoordinates;

  /**
   * Dimension of the Cuboid.
   */
  std::vector<int> dimensions;

  /**
   * Initial velocity of the Cuboid.
   */
  Vector<dim> initialVelocity;

  /**
   * Distance between the Particle(s).
   */
  double distance;

  /**
   * Mass of the Particle(s).
   */
  double mass;

  /**
   * Mean value of the Particle(s).
   */
  double meanValue;

  /**
   * CuboidArgument used to create Cuboid(s) by the Generator.
   * @param pStartingCoordinates coordinates of the lower left corner
   * @param pDimensions dimension of the Cuboid
   * @param pInitialVelocity initial velocity of the Cuboid (of each Particle)
   * @param pDistance distance between the Particle(s)
   * @param pMass mass of the Particle(s)
   * @param pMeanValue mean value of the Particle(s)
   */
  CuboidArgument(Vector<dim> pStartingCoordinates, std::vector<int> pDimensions, Vector<dim> pInitialVelocity,
                 double pDistance, double pMass, double pMeanValue = 0.1) : startingCoordinates{pStartingCoordinates},
                                                                            dimensions{std::move(pDimensions)},
                                                                            initialVelocity{pInitialVelocity},
                                                                            distance{pDistance}, mass{pMass},
                                                                            meanValue{pMeanValue} {

  }
};

/**
 * Compare operator for CuboidArgument(s);
 * @tparam dim dimension of current simulation
 * @param left first CuboidArgument
 * @param right second CuboidArgument
 * @return true if they equal
 */
template<size_t dim>
bool operator==(const CuboidArgument<dim> &left, const CuboidArgument<dim> &right) {
  return left.startingCoordinates == right.startingCoordinates && left.dimensions == right.dimensions
      && left.initialVelocity == right.initialVelocity && left.distance == right.distance && left.mass == right.mass
      && left.meanValue == right.meanValue;
}
