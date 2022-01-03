#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "generator/GeneratorArguments/RectangularArgument.h"

/**
 * Arguments used to create Cuboid(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class CuboidArgument : public RectangularArgument<CuboidArgument<dim>, dim> {

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
  double pDepthOfPotentialWell, int pType) : RectangularArgument<CuboidArgument<dim>, dim>{pStartingCoordinates, pDimensions, pInitialVelocity, pDistance, pMass, pMeanValue, pPacked,
        pZeroCrossing, pDepthOfPotentialWell, pType} {  }

  //----------------------------------------Methods----------------------------------------

  /**
   * Prints the CuboidArgument.
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\tCuboid:" << std::endl;
    argument << "\t\t\t\t Stating coordinates: " << ArrayUtils::to_string(RectangularArgument<CuboidArgument<dim>, dim>::getStartingCoordinates()) << std::endl;
    argument << "\t\t\t\t Dimension: " << ArrayUtils::to_string(RectangularArgument<CuboidArgument<dim>, dim>::getDimensions()) << std::endl;
    argument << "\t\t\t\t Velocity: " << ArrayUtils::to_string(RectangularArgument<CuboidArgument<dim>, dim>::getInitialVelocity()) << std::endl;
    argument << "\t\t\t\t Distance: " << RectangularArgument<CuboidArgument<dim>, dim>::getDistance() << std::endl;
    argument << "\t\t\t\t Mass: " << RectangularArgument<CuboidArgument<dim>, dim>::getMass() << std::endl;
    argument << "\t\t\t\t Mean value: " << RectangularArgument<CuboidArgument<dim>, dim>::getMeanValue() << std::endl;
    argument << "\t\t\t\t Packed: " << (RectangularArgument<CuboidArgument<dim>, dim>::getPacked() ? "true" : "false") << std::endl;
    argument << "\t\t\t\t Zero crossing: " << RectangularArgument<CuboidArgument<dim>, dim>::getZeroCrossing() << std::endl;
    argument << "\t\t\t\t Depth of potential well: " << RectangularArgument<CuboidArgument<dim>, dim>::getDepthOfPotentialWell() << std::endl;
    argument << "\t\t\t\t Type: " << RectangularArgument<CuboidArgument<dim>, dim>::getType() << std::endl;
    return argument.str();
  };
};
