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
  /**
   * Stiffness of the Membrane.
   */
  double stiffness;

  /**
   * Average bond length of the Membrane.
   */
  double averageBondLength;

  /**
   * True if the Membrane has a fixed outline.
   */
  bool fixedOutline;

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
   * @param pZeroCrossing is a point where the sign of a mathematical function changes
   * @param pDepthOfPotentialWell is the region surrounding a local minimum of potential energy
   * @param pStiffness is the stiffness constant of a molecule
   * @param pAverageBondLength is the average bond length of a molecule
   * @param pType of all particles generated with this specific generator argument
   * @param pFixed of all particles generated with this specific generator argument
   * @param pForces additional forces applied on the particles
   * @param pFixedOutline fixed outline
   */
  MembraneArgument(Vector<dim> pStartingCoordinates, std::array<int, dim> pDimensions, Vector<dim> pInitialVelocity,
                   double pDistance, double pMass, double pMeanValue, bool pPacked, double pZeroCrossing,
                   double pDepthOfPotentialWell, double pStiffness, double pAverageBondLength, int pType, bool pFixed,
                   std::vector<ForceContainer<dim>> pForces, bool pFixedOutline) : RectangularArgument<dim>{
      pStartingCoordinates, pDimensions, pInitialVelocity, pDistance, pMass, pMeanValue, pPacked, pZeroCrossing,
      pDepthOfPotentialWell, pType, pFixed, pForces}, stiffness{pStiffness}, averageBondLength{pAverageBondLength},
                                                                                   fixedOutline{pFixedOutline} {}


  //----------------------------------------Methods----------------------------------------

  /**
   * Prints the MembraneArgument.
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\tMembrane:" << std::endl;
    argument << "\t\t\t\t Stiffness: " << getStiffness() << std::endl;
    argument << "\t\t\t\t AverageBondLength: " << getAverageBondLength() << std::endl;
    argument << "\t\t\t\t Fixed outline: " << getFixedOutline() << std::endl;
    argument << RectangularArgument<dim>::toString();
    return argument.str();
  };

  //----------------------------------------Getter & Setter----------------------------------------

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
   * Getter for fixedOutline.
   * @return fixedOutline
   */
  [[nodiscard]] const bool &getFixedOutline() const {
    return fixedOutline;
  }
};
