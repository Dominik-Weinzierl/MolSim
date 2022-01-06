#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "generator/GeneratorArguments.h"

/**
 * Arguments used to create Rectangular Shape(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class RectangularArgument : public GeneratorArguments {

 private:
  /**
   * Coordinates of the lower left corner.
   */
  Vector<dim> startingCoordinates;

  /**
   * Dimension of the Shape.
   */
  std::array<int, dim> dimensions;

  /**
   * Initial velocity of the Shape.
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

  /**
   * Should the particles be fixed
   */
  bool fixed;

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * ShapeArgument used to create Shape(s) by the Generator.
   * @param pStartingCoordinates coordinates of the lower left corner
   * @param pDimensions dimension of the Shape
   * @param pInitialVelocity initial velocity of the Shape (of each Particle)
   * @param pDistance distance between the Particle(s)
   * @param pMass mass of the Particle(s)
   * @param pMeanValue mean value of the Particle(s)
   * @param pPacked describes if the Shape is packed with Particle(s)
   * @param pZeroCrossing is a point where the sign of a mathematical function changes.
   * @param pDepthOfPotentialWell is the region surrounding a local minimum of potential energy.
   * @param pType of all particles generated with this specific generator argument.
   * @param pFixed whether the particles should be fixed.
   */
  RectangularArgument(Vector<dim> pStartingCoordinates, std::array<int, dim> pDimensions, Vector<dim> pInitialVelocity,
                      double pDistance, double pMass, double pMeanValue, bool pPacked, double pZeroCrossing,
                      double pDepthOfPotentialWell, int pType, bool pFixed) : startingCoordinates{pStartingCoordinates},
                                                                              dimensions{std::move(pDimensions)},
                                                                              initialVelocity{pInitialVelocity},
                                                                              distance{pDistance}, mass{pMass},
                                                                              meanValue{pMeanValue}, packed{pPacked},
                                                                              zeroCrossing{pZeroCrossing},
                                                                              depthOfPotentialWell{
                                                                                  pDepthOfPotentialWell}, type{pType},
                                                                              fixed{pFixed} {

  }

  /**
   * Default destructor used for inheritance.
   */
  virtual ~RectangularArgument() = default;

  //----------------------------------------Methods----------------------------------------

  /**
  * Prints the RectangleArgument.
  */
  [[nodiscard]] virtual std::string toString() const = 0;

  /**
   * Stream operator for RectangleArgument(s).
   * @tparam dim dimension of our simulation.
   * @param stream std::ostream
   * @param p RectangleArgument to print
   * @return updated stream
   */
  friend std::ostream &operator<<(std::ostream &stream, const RectangularArgument &c) {
    stream << c.toString();
    return stream;
  }

  /**
   * Compare operator for RectangleArgument(s);
   * @tparam dim dimension of current simulation
   * @param left first RectangleArgument
   * @param right second RectangleArgument
   * @return true if they equal
   */
  friend bool operator==(const RectangularArgument &left, const RectangularArgument &right) {
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
