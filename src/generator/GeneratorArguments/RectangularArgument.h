#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "GeneratorArguments.h"

/**
 * Arguments used to create Rectangular Shape(s).
 * @tparam dim dimension of our simulation
 */
template<size_t dim>
class RectangularArgument : public GeneratorArguments<dim> {

 private:
  /**
   * Coordinates of the lower left corner.
   */
  Vector<dim> startingCoordinates;

  /**
   * Dimension of the Shape.
   */
  std::array<int, dim> dimensions;

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
   * @param pZeroCrossing is a point where the sign of a mathematical function changes
   * @param pDepthOfPotentialWell is the region surrounding a local minimum of potential energy
   * @param pType of all particles generated with this specific generator argument
   * @param pFixed whether the particles should be fixed
   * @param pForces additional forces applied on the particles
   */
  RectangularArgument(Vector<dim> pStartingCoordinates, std::array<int, dim> pDimensions, Vector<dim> pInitialVelocity,
                      double pDistance, double pMass, double pMeanValue, bool pPacked, double pZeroCrossing,
                      double pDepthOfPotentialWell, int pType, bool pFixed, std::vector<ForceContainer<dim>> pForces)
      : GeneratorArguments<dim>(pInitialVelocity, pDistance, pMass, pMeanValue, pPacked, pZeroCrossing,
                                pDepthOfPotentialWell, pType, pFixed, pForces),
        startingCoordinates{pStartingCoordinates}, dimensions{std::move(pDimensions)} {

  }

  /**
   * Default destructor used for inheritance.
   */
  virtual ~RectangularArgument() = default;

  //----------------------------------------Methods----------------------------------------

  /**
  * Prints the RectangleArgument.
  */
  [[nodiscard]] virtual std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\t\t Start coordinates: " << ArrayUtils::to_string(startingCoordinates) << std::endl;
    argument << "\t\t\t\t Dimension: " << ArrayUtils::to_string(dimensions) << std::endl;
    argument << GeneratorArguments<dim>::toString();
    return argument.str();
  };

  /**
   * Compare operator for RectangularArgument(s);
   * @param rhs RectangularArgument
   * @return true if they equal
   */
  bool operator==(const RectangularArgument &rhs) const {
    return static_cast<const GeneratorArguments<dim> &>(*this) == static_cast<const GeneratorArguments<dim> &>(rhs)
        && startingCoordinates == rhs.startingCoordinates && dimensions == rhs.dimensions;
  }

  /**
   * Compare operator for RectangularArgument(s);
   * @param rhs GeneratorArgument
   * @return true if they not equal
   */
  bool operator!=(const RectangularArgument &rhs) const {
    return !(rhs == *this);
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
};
