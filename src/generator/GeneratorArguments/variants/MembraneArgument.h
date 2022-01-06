#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "generator/GeneratorArguments/RectangularArgument.h"

/**
 * Arguments used to create Membrane(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class MembraneArgument : public RectangularArgument<dim> {

 private:
  double stiffness;
  double averageBondLength;

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * MembraneArgument used to create Membrane(s) by the Generator.
   * @param pStartingCoordinates coordinates of the lower left corner
   * @param pDimensions dimension of the Membrane
   * @param pInitialVelocity initial velocity of the Membrane (of each Particle)
   * @param pDistance distance between the Particle(s)
   * @param pMass mass of the Particle(s)
   * @param pMeanValue mean value of the Particle(s)
   * @param pPacked describes if the Membrane is packed with Particle(s)
   * @param pZeroCrossing is a point where the sign of a mathematical function changes.
   * @param pDepthOfPotentialWell is the region surrounding a local minimum of potential energy.
   * @param pType of all particles generated with this specific generator argument.
   * @param pFixed of all particles generated with this specific generator argument.
   */
  MembraneArgument(Vector<dim> pStartingCoordinates, std::array<int, dim> pDimensions, Vector<dim> pInitialVelocity,
                   double pDistance, double pMass, double pMeanValue, bool pPacked, double pZeroCrossing,
                   double pDepthOfPotentialWell, double pStiffness, double pAverageBondLength, int pType, bool pFixed)
      : RectangularArgument<dim>{pStartingCoordinates, pDimensions, pInitialVelocity, pDistance, pMass, pMeanValue,
                                 pPacked, pZeroCrossing, pDepthOfPotentialWell, pType, pFixed}, stiffness{pStiffness},
        averageBondLength{pAverageBondLength} {}

  //----------------------------------------Methods----------------------------------------

  /**
   * Getter for stiffness.
   * @return stiffness
   */
  [[nodiscard]] const double &getStiffness() const {
    return stiffness;
  }

  /**
   * Getter for averageBondLength.
   * @return averageBondLength
   */
  [[nodiscard]] const double &getAverageBondLength() const {
    return averageBondLength;
  }

  /**
   * Prints the MembraneArgument.
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\tMembrane:" << std::endl;
    argument << "\t\t\t\t Stating coordinates: "
             << ArrayUtils::to_string(RectangularArgument<dim>::getStartingCoordinates()) << std::endl;
    argument << "\t\t\t\t Dimension: " << ArrayUtils::to_string(RectangularArgument<dim>::getDimensions()) << std::endl;
    argument << "\t\t\t\t Velocity: " << ArrayUtils::to_string(RectangularArgument<dim>::getInitialVelocity())
             << std::endl;
    argument << "\t\t\t\t Distance: " << RectangularArgument<dim>::getDistance() << std::endl;
    argument << "\t\t\t\t Mass: " << RectangularArgument<dim>::getMass() << std::endl;
    argument << "\t\t\t\t Mean value: " << RectangularArgument<dim>::getMeanValue() << std::endl;
    argument << "\t\t\t\t Packed: " << (RectangularArgument<dim>::getPacked() ? "true" : "false") << std::endl;
    argument << "\t\t\t\t Zero crossing: " << RectangularArgument<dim>::getZeroCrossing() << std::endl;
    argument << "\t\t\t\t Depth of potential well: " << RectangularArgument<dim>::getDepthOfPotentialWell()
             << std::endl;
    argument << "\t\t\t\t Stiffness: " << getStiffness() << std::endl;
    argument << "\t\t\t\t AverageBondLength: " << getAverageBondLength() << std::endl;
    argument << "\t\t\t\t Type: " << RectangularArgument<dim>::getType() << std::endl;
    return argument.str();
  };
};
