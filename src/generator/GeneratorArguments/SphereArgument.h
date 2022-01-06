#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"

/**
 * Arguments used to create Sphere(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class SphereArgument : public GeneratorArguments<dim> {

  /**
   * Coordinates of the center.
   */
  Vector<dim> centerCoordinates;

  /**
   * Radius of the Sphere.
   */
  int radius;

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
 * SphereArgument used to create Sphere(s) by the Generator.
 * @param pCenterCoordinates coordinates of the center
 * @param pRadius radius of the Sphere
 * @param pInitialVelocity initial velocity of the Sphere (of each Particle)
 * @param pDistance distance between the Particle(s)
 * @param pMass mass of the Particle(s)
 * @param pMeanValue mean value of the Particle(s)
 * @param pPacked describes if the Cuboid is packed with Particle(s)
 * @param pZeroCrossing is a point where the sign of a mathematical function changes.
 * @param pDepthOfPotentialWell is the region surrounding a local minimum of potential energy.
 * @param pType of all particles generated with this specific generator argument.
 * @param pFixed whether the particles should be fixed.
 * @param pForces additional forces applied on the particles.
 */
  SphereArgument(Vector<dim> pCenterCoordinates, int pRadius, Vector<dim> pInitialVelocity, double pDistance,
                 double pMass, double pMeanValue, bool pPacked, double pZeroCrossing, double pDepthOfPotentialWell,
                 int pType, bool pFixed, std::vector<ForceContainer<dim>> pForces) : GeneratorArguments<dim>(
      pInitialVelocity, pDistance, pMass, pMeanValue, pPacked, pZeroCrossing, pDepthOfPotentialWell, pType, pFixed,
      pForces), centerCoordinates{pCenterCoordinates}, radius{pRadius} {
  }

  //----------------------------------------Methods----------------------------------------

  /**
   * Prints the SphereArgument.
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\tSphere:" << std::endl;
    argument << "\t\t\t\t Center coordinates: " << ArrayUtils::to_string(centerCoordinates) << std::endl;
    argument << "\t\t\t\t Radius: " << radius << std::endl;
    argument << GeneratorArguments<dim>::toString() << std::endl;
    return argument.str();
  };

  /**
   * Compare operator for SphereArgument(s);
   * @param rhs SphereArgument
   * @return true if they not equal
   */
  bool operator==(const SphereArgument &rhs) const {
    return static_cast<const GeneratorArguments<dim> &>(*this) == static_cast<const GeneratorArguments<dim> &>(rhs)
        && centerCoordinates == rhs.centerCoordinates && radius == rhs.radius;
  }

  /**
   * Compare operator for SphereArgument(s);
   * @param rhs GeneratorArgument
   * @return true if they not equal
   */
  bool operator!=(const SphereArgument &rhs) const {
    return !(rhs == *this);
  }

  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * Getter for the centerCoordinates.
   * @return centerCoordinates
   */
  const Vector<dim> &getCenterCoordinates() const {
    return centerCoordinates;
  }

  /**
   * Getter for the radius.
   * @return radius
   */
  [[nodiscard]] int getRadius() const {
    return radius;
  }
};
