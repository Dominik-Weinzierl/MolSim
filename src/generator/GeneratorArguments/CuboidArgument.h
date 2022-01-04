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
   * Should the particles be fixed
   */
  bool fixed;

  /**
   * Coordinates of the lower left corner.
   */
  Vector<dim> startingCoordinates;

  /**
   * Dimension of the Cuboid.
   */
  std::array<int, dim> dimensions;

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
   * Packed value of the Particle(s).
   */
  bool packed;

  /**
   * A zero-crossing is a point where the sign of a mathematical function changes.
   */
  double zeroCrossing;

  /**
   * A potential well is the region surrounding a local minimum of potential energy.
   */
  double depthOfPotentialWell;

  /**
   * Type of all particles generated with this specific generator argument.
   */
  int type;

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
  * CuboidArgument used to create Cuboid(s) by the Generator.
  * @param pStartingCoordinates coordinates of the lower left corner
  * @param pDimensions dimension of the Cuboid
  * @param pInitialVelocity initial velocity of the Cuboid (of each Particle)
  * @param pDistance distance between the Particle(s)
  * @param pMass mass of the Particle(s)
  * @param pMeanValue mean value of the Particle(s)
  * @param pPacked describes if the Cuboid is packed with Particle(s)
  * @param pZeroCrossing is a point where the sign of a mathematical function changes.
  * @param pDepthOfPotentialWell is the region surrounding a local minimum of potential energy.
  * @param pType of all particles generated with this specific generator argument.
  */
  CuboidArgument(Vector<dim> pStartingCoordinates, std::array<int, dim> pDimensions, Vector<dim> pInitialVelocity,
                 double pDistance, double pMass, double pMeanValue, bool pPacked, double pZeroCrossing,
                 double pDepthOfPotentialWell, int pType) : startingCoordinates{pStartingCoordinates},
                                                            dimensions{std::move(pDimensions)},
                                                            initialVelocity{pInitialVelocity}, distance{pDistance},
                                                            mass{pMass}, meanValue{pMeanValue}, packed{pPacked},
                                                            zeroCrossing{pZeroCrossing},
                                                            depthOfPotentialWell{pDepthOfPotentialWell}, type{pType},
                                                            fixed{false} {

  }

  /**
   * CuboidArgument used to create Cuboid(s) by the Generator.
   * @param pStartingCoordinates coordinates of the lower left corner
   * @param pDimensions dimension of the Cuboid
   * @param pInitialVelocity initial velocity of the Cuboid (of each Particle)
   * @param pDistance distance between the Particle(s)
   * @param pMass mass of the Particle(s)
   * @param pMeanValue mean value of the Particle(s)
   * @param pPacked describes if the Cuboid is packed with Particle(s)
   * @param pZeroCrossing is a point where the sign of a mathematical function changes.
   * @param pDepthOfPotentialWell is the region surrounding a local minimum of potential energy.
   * @param pType of all particles generated with this specific generator argument.
   * @param pFixed whether the particles should be fixed.
   */
  CuboidArgument(Vector<dim> pStartingCoordinates, std::array<int, dim> pDimensions, Vector<dim> pInitialVelocity,
                 double pDistance, double pMass, double pMeanValue, bool pPacked, double pZeroCrossing,
                 double pDepthOfPotentialWell, int pType, bool pFixed) : startingCoordinates{pStartingCoordinates},
                                                                         dimensions{std::move(pDimensions)},
                                                                         initialVelocity{pInitialVelocity},
                                                                         distance{pDistance}, mass{pMass},
                                                                         meanValue{pMeanValue}, packed{pPacked},
                                                                         zeroCrossing{pZeroCrossing},
                                                                         depthOfPotentialWell{pDepthOfPotentialWell},
                                                                         type{pType}, fixed{pFixed} {

  }

  //----------------------------------------Methods----------------------------------------

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
    argument << "\t\t\t\t Packed: " << (packed ? "true" : "false") << std::endl;
    argument << "\t\t\t\t Zero crossing: " << zeroCrossing << std::endl;
    argument << "\t\t\t\t Depth of potential well: " << depthOfPotentialWell << std::endl;
    argument << "\t\t\t\t Type: " << type << std::endl;
    return argument.str();
  };

  /**
   * Stream operator for CuboidArgument(s).
   * @tparam dim dimension of our simulation.
   * @param stream std::ostream
   * @param p CuboidArgument to print
   * @return updated stream
   */
  friend std::ostream &operator<<(std::ostream &stream, const CuboidArgument<dim> &c) {
    stream << c.toString();
    return stream;
  }

  /**
   * Compare operator for CuboidArgument(s);
   * @tparam dim dimension of current simulation
   * @param left first CuboidArgument
   * @param right second CuboidArgument
   * @return true if they equal
   */
  friend bool operator==(const CuboidArgument<dim> &left, const CuboidArgument<dim> &right) {
    return left.getStartingCoordinates() == right.getStartingCoordinates()
        && left.getDimensions() == right.getDimensions() && left.getInitialVelocity() == right.getInitialVelocity()
        && left.getDistance() == right.getDistance() && left.getMass() == right.getMass()
        && left.getMeanValue() == right.getMeanValue() && left.getPacked() == right.getPacked()
        && left.getDepthOfPotentialWell() == right.getDepthOfPotentialWell()
        && left.getZeroCrossing() == right.getZeroCrossing() && left.getType() == right.getType();
  }

  //----------------------------------------Getter & Setter----------------------------------------

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
  [[nodiscard]] const std::array<int, dim> &getDimensions() const {
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
 * Getter for isStatic
 * @return isStatic
 */
  [[nodiscard]] bool isFixed() const {
    return fixed;
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
   * Getter for the packed.
   * @return packed
   */
  [[nodiscard]] bool getPacked() const {
    return packed;
  }

  /**
   * Getter for the zero crossing of all generated particles.
   * @return double zeroCrossing
   */
  [[nodiscard]] double getZeroCrossing() const {
    return zeroCrossing;
  }

  /**
   * Getter for the potential well.
   * @return double depthOfPotentialWell
   */
  [[nodiscard]] double getDepthOfPotentialWell() const {
    return depthOfPotentialWell;
  }

  /**
   * Getter for the type of the generated Particle(s).
   * @return int type
   */
  [[nodiscard]] int getType() const {
    return type;
  }
};
