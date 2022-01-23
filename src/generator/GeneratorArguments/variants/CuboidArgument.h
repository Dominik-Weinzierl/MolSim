#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "generator/GeneratorArguments/RectangularArgument.h"

/**
 * Arguments used to create Cuboid(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class CuboidArgument : public RectangularArgument<dim> {

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
   * @param pZeroCrossing is a point where the sign of a mathematical function changes
   * @param pDepthOfPotentialWell is the region surrounding a local minimum of potential energy
   * @param pType of all particles generated with this specific generator argument
   * @param pFixed of all particles generated with this specific generator argument
   * @param pForces additional forces applied on the particles
   */
  CuboidArgument(Vector<dim> pStartingCoordinates, std::array<int, dim> pDimensions, Vector<dim> pInitialVelocity,
                 double pDistance, double pMass, double pMeanValue, bool pPacked, double pZeroCrossing,
                 double pDepthOfPotentialWell, int pType, bool pFixed, std::vector<ForceContainer<dim>> pForces) : RectangularArgument<dim>{pStartingCoordinates,
                                                                                                  pDimensions,
                                                                                                  pInitialVelocity,
                                                                                                  pDistance, pMass,
                                                                                                  pMeanValue, pPacked,
                                                                                                  pZeroCrossing,
                                                                                                  pDepthOfPotentialWell, pType,
                                                                                                  pFixed, pForces} {}

  //----------------------------------------Methods----------------------------------------

  /**
   * Prints the CuboidArgument.
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\tCuboid:" << std::endl;
    argument << RectangularArgument<dim>::toString();
    return argument.str();
  };
};
