#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

/**
 * Arguments used to create Cuboid(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class CuboidArgument : public GeneratorArguments {
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

 public:

  /**
   * Getter for the startingCoordinates.
   * @return startingCoordinates
   */
  const Vector<dim> &getStartingCoordinates() const {
    return startingCoordinates;
  }

  /**
   * Getter for the dimensions.
   * @return dimensions
   */
  [[nodiscard]] const std::vector<int> &getDimensions() const {
    return dimensions;
  }

  /**
   * Getter for the initialVelocity.
   * @return initialVelocity
   */
  const Vector<dim> &getInitialVelocity() const {
    return initialVelocity;
  }

  /**
   * Getter for the distance.
   * @return distance
   */
  [[nodiscard]] double getDistance() const {
    return distance;
  }

  /**
   * Getter for the mass.
   * @return mass
   */
  [[nodiscard]] double getMass() const {
    return mass;
  }

  /**
   * Getter for the meanValue.
   * @return meanValue
   */
  [[nodiscard]] double getMeanValue() const {
    return meanValue;
  }

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

  /**
   * Prints the CuboidArgument.
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\tCuboid:" << std::endl;
    argument << "\t\t\t\t Stating coordinates: " << ArrayUtils::to_string(startingCoordinates) << std::endl;
    argument << "\t\t\t\t Dimension: " << ArrayUtils::to_string(dimensions) << std::endl;
    argument << "\t\t\t\t Velocity: " << ArrayUtils::to_string(initialVelocity) << std::endl;
    argument << "\t\t\t\t Distance: " << distance << std::endl;
    argument << "\t\t\t\t Mass: " << mass << std::endl;
    argument << "\t\t\t\t Mean value: " << meanValue << std::endl;
    return argument.str();
  };
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
  return left.getStartingCoordinates() == right.getStartingCoordinates()
      && left.getDimensions() == right.getDimensions() && left.getInitialVelocity() == right.getInitialVelocity()
      && left.getDistance() == right.getDistance() && left.getMass() == right.getMass()
      && left.getMeanValue() == right.getMeanValue();
}

/**
 * Stream operator for CuboidArgument(s).
 * @tparam dim dimension of our simulation.
 * @param stream std::ostream
 * @param p CuboidArgument to print
 * @return updated stream
 */
template<size_t dim>
std::ostream &operator<<(std::ostream &stream, const CuboidArgument<dim> &c) {
  stream << c.toString();
  return stream;
}

