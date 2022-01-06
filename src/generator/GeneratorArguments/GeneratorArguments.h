#pragma once

/**
 * Used as super class for other GeneratorArgument(s).
 */
template<size_t dim>
struct GeneratorArguments {
 protected:
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

  /**
   * Should the particles be fixed
   */
  bool fixed;

  /**
   *
   */
   std::vector<ForceContainer<dim>> forces;

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * GeneratorArgument used by the Generator.
   * @param pInitialVelocity initial velocity of the Shape (of each Particle)
   * @param pDistance distance between the Particle(s)
   * @param pMass mass of the Particle(s)
   * @param pMeanValue mean value of the Particle(s)
   * @param pPacked describes if the Shape is packed with Particle(s)
   * @param pZeroCrossing is a point where the sign of a mathematical function changes.
   * @param pDepthOfPotentialWell is the region surrounding a local minimum of potential energy.
   * @param pType of all particles generated with this specific generator argument.
   * @param pFixed whether the particles should be fixed.
   * @param pForces additional forces applied on the particles.
   */
  GeneratorArguments(Vector<dim> pInitialVelocity, double pDistance, double pMass, double pMeanValue, bool pPacked,
                     double pZeroCrossing, double pDepthOfPotentialWell, int pType, bool pFixed, std::vector<ForceContainer<dim>> pForces) : initialVelocity{
      pInitialVelocity}, distance{pDistance}, mass{pMass}, meanValue{pMeanValue}, packed{pPacked}, zeroCrossing{
      pZeroCrossing}, depthOfPotentialWell{pDepthOfPotentialWell}, type{pType}, fixed{pFixed}, forces{pForces} {

  }

  virtual ~GeneratorArguments() = default;

  //----------------------------------------Methods----------------------------------------

  /**
   * Prints the GeneratorArgument.
   */
  [[nodiscard]] virtual std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\t\t Velocity: " << ArrayUtils::to_string(initialVelocity) << std::endl;
    argument << "\t\t\t\t Distance: " << distance << std::endl;
    argument << "\t\t\t\t Mass: " << mass << std::endl;
    argument << "\t\t\t\t Mean value: " << meanValue << std::endl;
    argument << "\t\t\t\t Packed: " << (packed ? "true" : "false") << std::endl;
    argument << "\t\t\t\t Zero crossing: " << zeroCrossing << std::endl;
    argument << "\t\t\t\t Depth of potential well: " << depthOfPotentialWell << std::endl;
    argument << "\t\t\t\t Type: " << type << std::endl;
    argument << "\t\t\t\t Fixed: " << fixed << std::endl;
    //TODO Add force container
    return argument.str();
  };

  /**
   * Compare operator for GeneratorArgument(s);
   * @param rhs GeneratorArgument
   * @return true if they equal
   */
  bool operator==(const GeneratorArguments &rhs) const {
    return initialVelocity == rhs.initialVelocity && distance == rhs.distance && mass == rhs.mass
        && meanValue == rhs.meanValue && packed == rhs.packed && zeroCrossing == rhs.zeroCrossing
        && depthOfPotentialWell == rhs.depthOfPotentialWell && type == rhs.type && fixed == rhs.fixed;
  }

  /**
   * Compare operator for GeneratorArgument(s);
   * @param rhs GeneratorArgument
   * @return true if they not equal
   */
  bool operator!=(const GeneratorArguments &rhs) const {
    return !(rhs == *this);
  }

  /**
   * Stream operator for GeneratorArgument(s).
   * @tparam dim dimension of our simulation.
   * @param stream std::ostream
   * @param p SphereArgument to print
   * @return updated stream
   */
  friend std::ostream &operator<<(std::ostream &stream, const GeneratorArguments<dim> &s) {
    stream << s.toString();
    return stream;
  }

  //----------------------------------------Getter & Setter----------------------------------------


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
* Getter for fixed
* @return fixed
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
