#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

/**
 * Arguments used to create Sphere(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class SphereArgument : public GeneratorArguments {
 public:
  /**
   * Coordinates of the center.
   */
  Vector<dim> centerCoordinates;

  /**
   * Radius of the Sphere.
   */
  int radius;

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
   * SphereArgument used to create Sphere(s) by the Generator.
   * @param pCenterCoordinates coordinates of the center
   * @param pRadius radius of the Sphere
   * @param pInitialVelocity initial velocity of the Sphere (of each Particle)
   * @param pDistance distance between the Particle(s)
   * @param pMass mass of the Particle(s)
   * @param pMeanValue mean value of the Particle(s)
   */
  SphereArgument(Vector<dim> pCenterCoordinates, int pRadius, Vector<dim> pInitialVelocity, double pDistance,
                 double pMass, double pMeanValue = 0.1) : centerCoordinates{pCenterCoordinates}, radius{pRadius},
                                                          initialVelocity{pInitialVelocity}, distance{pDistance},
                                                          mass{pMass}, meanValue{pMeanValue} {
  }

};

/**
 * Compare operator for SphereArgument(s);
 * @tparam dim dimension of current simulation
 * @param left first SphereArgument
 * @param right second SphereArgument
 * @return true if they equal
 */
template<size_t dim>
bool operator==(const SphereArgument<dim> &left, const SphereArgument<dim> &right) {
  return left.centerCoordinates == right.centerCoordinates && left.radius == right.radius
      && left.initialVelocity == right.initialVelocity && left.distance == right.distance && left.mass == right.mass
      && left.meanValue == right.meanValue;
}
