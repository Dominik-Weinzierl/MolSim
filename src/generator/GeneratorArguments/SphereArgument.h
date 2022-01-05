#pragma once

#include "generator/Generator.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "generator/GeneratorArguments.h"

/**
 * Arguments used to create Sphere(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class SphereArgument : public GeneratorArguments {

 private:
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
   */
  SphereArgument(Vector<dim> pCenterCoordinates, int pRadius, Vector<dim> pInitialVelocity, double pDistance,
                 double pMass, double pMeanValue, bool pPacked, double pZeroCrossing, double pDepthOfPotentialWell,
                 int pType) : centerCoordinates{pCenterCoordinates}, radius{pRadius}, initialVelocity{pInitialVelocity},
                              distance{pDistance}, mass{pMass}, meanValue{pMeanValue}, packed{pPacked},
                              zeroCrossing{pZeroCrossing}, depthOfPotentialWell{pDepthOfPotentialWell}, type{pType} {
  }

  //----------------------------------------Methods----------------------------------------

  /**
   * Prints the SphereArgument.
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\tSphere:" << std::endl;
    argument << "\t\t\t\t Center coordinates: " << ArrayUtils::to_string(centerCoordinates) << std::endl;
    argument << "\t\t\t\t Velocity: " << ArrayUtils::to_string(initialVelocity) << std::endl;
    argument << "\t\t\t\t Radius: " << radius << std::endl;
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
   * Compare operator for SphereArgument(s);
   * @tparam dim dimension of current simulation
   * @param left first SphereArgument
   * @param right second SphereArgument
   * @return true if they equal
   */
  friend bool operator==(const SphereArgument<dim> &left, const SphereArgument<dim> &right) {
    return left.getCenterCoordinates() == right.getCenterCoordinates() && left.getRadius() == right.getRadius()
        && left.getInitialVelocity() == right.getInitialVelocity() && left.getDistance() == right.getDistance()
        && left.getMass() == right.getMass() && left.getMeanValue() == right.getMeanValue()
        && left.getPacked() == right.getPacked() && left.getDepthOfPotentialWell() == right.getDepthOfPotentialWell()
        && left.getZeroCrossing() == right.getZeroCrossing() && left.getType() == right.getType();
  }

  /**
   * Stream operator for SphereArgument(s).
   * @tparam dim dimension of our simulation.
   * @param stream std::ostream
   * @param p SphereArgument to print
   * @return updated stream
   */
  friend std::ostream &operator<<(std::ostream &stream, const SphereArgument<dim> &s) {
    stream << s.toString();
    return stream;
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
