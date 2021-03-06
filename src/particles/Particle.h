#pragma once

#include <string>

#include "physics/Vector/Vector.h"
#include "logger/Logger.h"
#include "physics/Forces/Force.h"

enum ParticleType {
  MOLECULE, PARTICLE
};
/**
 * Particle is a class that wraps up the properties of a particle, getters, setters and standard methods.
 * @tparam dim dimension of our simulation
 */
template<size_t dim>
class Particle {
 private:

  /**
   * Position of the particle.
   */
  Vector<dim> x;

  /**
   * Velocity of the particle.
   */
  Vector<dim> v;

  /**
   * Force effective on this particle.
   */
  Vector<dim> f;

  /**
   * Force which was effective on this particle.
   */
  Vector<dim> old_f;

  /**
   * Mass of this particle.
   */
  double m;

  /**
   * Type of the particle (0 -> normal Particle, -1 -> outflow)
   */
  int type;

  /**
   * A zero-crossing is a point where the sign of a mathematical function changes.
   */
  double zeroCrossing = 1;

  /**
   * A potential well is the region surrounding a local minimum of potential energy.
   */
  double potentialWellDepth = 5;

  /**
    * Whether the particle should be considered fixed (aka does not move)
    */
  bool fixed{};

  /**
   * Vector of moleculeArguments (only for MOLECULE).
   */
  std::vector<double> membraneArguments;

  /**
   * Vector of neighbours (only for MOLECULE).
   */
  std::vector<Particle<dim> *> neighbours;

  /**
   * Vector of diagonalNeighbours (only for MOLECULE).
   */
  std::vector<Particle<dim> *> diagonalNeighbours;

  /**
   * ParticleTypes (either PARTICLE or MOLECULE, default PARTICLE)
   */
  ParticleType particleType = PARTICLE;

  /**
   * Additional Forces applied to the Particle.
   */
  std::vector<Force<dim>> additionalForces{};

 public:

  //----------------------------------------Constructor & Destructor----------------------------------------

  /**
   * Default constructor.
   * @param type Default value 0
   */
  explicit Particle(int type_arg) : x{}, v{}, f{}, old_f{}, m{}, type{type_arg} {
    SPDLOG_TRACE("Particle generated");
  }

  /**
   * Copy constructor.
   * @param other Particle to copy
   */
  Particle(const Particle &other) = default;

  /**
   * Constructor which generates a particle with the given parameters.
   * @param pX position vector
   * @param pV velocity vector
   * @param pM mass
   * @param pType type of the Particle
   */
  Particle(const Vector<dim> &pX, const Vector<dim> &pV, double pM, int pType = 0) : x{pX}, v{pV}, f{}, old_f{}, m{pM},
                                                                                     type{pType} {
    SPDLOG_TRACE("Particle generated");
  }

  /**
  * Constructor which generates a particle with the given parameters.
   * @param pX position vector
   * @param pV velocity vector
   * @param pM mass
   * @param pZeroCrossing zero crossing
   * @param pPotentialWellDepth potential well depth
   * @param pType type of the Particle
   */
  Particle(const Vector<dim> &pX, const Vector<dim> &pV, double pM, double pZeroCrossing, double pPotentialWellDepth,
           int pType) : x{pX}, v{pV}, f{}, old_f{}, m{pM}, type{pType}, zeroCrossing{pZeroCrossing},
                        potentialWellDepth{pPotentialWellDepth}, fixed{false} {
    SPDLOG_TRACE("Particle generated");
  }

  /**
   * Constructor which generates a particle with the given parameters.
   * @param pX position vector
   * @param pV velocity vector
   * @param pM mass
   * @param pZeroCrossing zero crossing
   * @param pPotentialWellDepth potential well depth
   * @param pType type of the Particle
   * @param pFixed if the particle should be fixed
   */
  Particle(const Vector<dim> &pX, const Vector<dim> &pV, double pM, double pZeroCrossing, double pPotentialWellDepth,
           int pType, bool pFixed) : x{pX}, f{}, old_f{}, m{pM}, type{pType}, zeroCrossing{pZeroCrossing},
                                     potentialWellDepth{pPotentialWellDepth}, fixed{pFixed} {
    if (fixed) {
      v = {};
    } else
      v = pV;
    SPDLOG_TRACE("Particle generated");
  }

  /**
   * Constructor which generates a particle with the given parameters.
   * @param pX position vector
   * @param pV velocity vector
   * @param pF force vector
   * @param pOldF old force vector
   * @param pM mass
   * @param pZeroCrossing zero crossing
   * @param pPotentialWellDepth potential well depth
   * @param pType type of the Particle
   */
  Particle(const Vector<dim> &pX, const Vector<dim> &pV, const Vector<dim> &pF, const Vector<dim> &pOldF, double pM,
           double pZeroCrossing, double pPotentialWellDepth, int pType) : x{pX}, v{pV}, f{pF}, old_f{pOldF}, m{pM},
                                                                          type{pType}, zeroCrossing{pZeroCrossing},
                                                                          potentialWellDepth{pPotentialWellDepth} {
    SPDLOG_TRACE("Particle generated");
  }

  /**
   * Default destructor.
   */
  virtual ~Particle() = default;

  //----------------------------------------Methods----------------------------------------

  /**
   * Methods to update the force.
   * @param x_arg new x value to add
   * @param y_arg new y value to add
   * @param z_arg new z value to add
   */
  inline void updateForce(double x_arg, double y_arg, double z_arg) {
    if (fixed)
      return;
    f[0] += x_arg;
    f[1] += y_arg;
    f[2] += z_arg;
  }

  /**
   * Methods to update the force.
   * @param x_arg new x value to add
   * @param y_arg new y value to add
   */
  inline void updateForce(double x_arg, double y_arg) {
    if (fixed)
      return;
    f[0] += x_arg;
    f[1] += y_arg;
  }

  /**
   * Methods to update the force.
   * @param force new force to add
   */
  inline void updateForce(std::array<double, dim> force) {
    if (fixed)
      return;
    for (size_t i = 0; i < dim; ++i) {
      f[i] += force[i];
    }
  }

  /**
   * Operator which allows the comparison of the particle to a given particle.
   * @param other Particle
   * @return True, if the given Particle equals this Particle
   */
  bool operator==(const Particle &other) {
    return (x == other.x) and (v == other.v) and (f == other.f) and (type == other.type) and (m == other.m)
        and (old_f == other.old_f);
  }

  /**
   * Method which returns the properties of the particle as a String.
   * @return properties of the particle as a String
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream stream;
    stream << "Particle: X:" << x << " v: " << v << " f: " << f << " old_f: " << old_f << " type: " << type;
    return stream.str();
  }

  /**
   * Stream operator for Particle(s).
   * @tparam dim dimension of our simulation.
   * @param stream std::ostream
   * @param p Particle to print
   * @return updated stream
   */
  friend std::ostream &operator<<(std::ostream &stream, const Particle<dim> &p) {
    stream << p.toString();
    return stream;
  }

  /**
   * Operator == to compare Particles for testing
   * @tparam dim Dimension of the given Particles
   * @param p1 One of the two Particles to compare
   * @param p2 One of the two Particles to compare
   * @return True, if both Particles are the same
   */
  friend bool operator==(const Particle<dim> &p1, const Particle<dim> &p2) {
    return p1.getX() == p2.getX() && p1.getV() == p2.getV() && p1.getM() == p2.getM() && p1.getF() == p2.getF()
        && p1.getOldF() == p2.getOldF() && p1.getType() == p2.getType();
  }

  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * Getter for the position of the Particle.
   * @return position of the Particle x
   */
  [[nodiscard]] const Vector<dim> &getX() const {
    return x;
  }

  /**
   * Getter for the velocity of the Particle.
   * @return velocity of the Particle v
   */
  [[nodiscard]] const Vector<dim> &getV() const {
    return v;
  }

  /**
   * Getter for the force of the Particle.
   * @return force of the Particle f
   */
  [[nodiscard]] const Vector<dim> &getF() const {
    return f;
  }

  /**
   * Getter for the old force of the Particle.
   * @return old force of the Particle old_f
   */
  [[nodiscard]] const Vector<dim> &getOldF() const {
    return old_f;
  }

  /**
   * Getter for the mass of the Particle.
   * @return mass of the Particle m
   */
  [[nodiscard]] const double &getM() const {
    return m;
  }

  /**
   * Getter for the type of the Particle.
   * @return type of the Particle type
   */
  [[nodiscard]] int getType() const {
    return type;
  }

  /**
   * Getter for the zeroCrossing of the Particle.
   * @return zeroCrossing of the Particle
   */
  [[nodiscard]] double getZeroCrossing() const {
    return zeroCrossing;
  }

  /**
   * Getter for the potentialWellDepth of the Particle.
   * @return potentialWellDepth of the Particle
   */
  [[nodiscard]] double getPotentialWellDepth() const {
    return potentialWellDepth;
  }

  /**
   * Getter for fixed
   * @return true iff the particle is fixed
   */
  [[nodiscard]] inline bool isFixed() const {
    return fixed;
  }

  /**
   * Getter for neighbours.
   * @return neighbours
   */
  [[nodiscard]] const std::vector<Particle<dim> *> &getNeighbours() const {
      return neighbours;
  }

  /**
   * Getter for diagonalNeighbours.
   * @return diagonalNeighbours
   */
  [[nodiscard]] const std::vector<Particle<dim> *> &getDiagonalNeighbours() const {
      return diagonalNeighbours;
  }

  /**
  * Getter for membraneArguments.
  * @return membraneArguments
  */
  [[nodiscard]] std::vector<double> getMembraneArguments() const {
    if (particleType == MOLECULE)
      return membraneArguments;
    else
      return {};
  }

  /**
   * Getter for particleType.
   * @return particleType
   */
  [[nodiscard]] ParticleType getParticleType() const {
    return particleType;
  }

  /**
   * Setter for the position of the Particle.
   * @param position new position
   */
  inline void setX(const Vector<dim> &position) {
    x = position;
  }

  /**
   * Setter for the position of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   * @param z_arg new z value
   */
  inline void setX(double x_arg, double y_arg, double z_arg) {
    x[0] = x_arg;
    x[1] = y_arg;
    x[2] = z_arg;
  }

  /**
   * Setter for the position of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   */
  inline void setX(double x_arg, double y_arg) {
    x[0] = x_arg;
    x[1] = y_arg;
  }

  /**
   * Setter for the velocity of the Particle.
   * @param velocity new velocity
   */
  inline void setV(const Vector<dim> &velocity) {
    if (fixed)
      return;
    v = velocity;
  }

  /**
   * Setter for the velocity of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   * @param z_arg new z value
   */
  inline void setV(double x_arg, double y_arg, double z_arg) {
    if (fixed)
      return;
    v[0] = x_arg;
    v[1] = y_arg;
    v[2] = z_arg;
  }

  /**
   * Setter for the velocity of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   */
  inline void setV(double x_arg, double y_arg) {
    if (fixed)
      return;
    v[0] = x_arg;
    v[1] = y_arg;
  }

  /**
   * Setter for the force of the Particle.
   * @param force new force
   */
  inline void setF(const Vector<dim> &force) {
    f = force;
  }

  /**
   * Setter for the force of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   * @param z_arg new z value
   */
  inline void setF(double x_arg, double y_arg, double z_arg) {
    f[0] = x_arg;
    f[1] = y_arg;
    f[2] = z_arg;
  }

  /**
   * Setter for the force of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   */
  inline void setF(double x_arg, double y_arg) {
    f[0] = x_arg;
    f[1] = y_arg;
  }

  /**
   * Setter for the force of the Particle.
   * @param y_arg new y value
   */
  inline void setF(double y_arg) {
    f[0] = 0;
    f[1] = y_arg;
    if (dim == 3)
      f[2] = 0;
  }

  /**
   * Setter for the old force of the Particle.
   * @param oldForce new old force
   */
  inline void setOldF(const Vector<dim> &oldForce) {
    old_f = oldForce;
  }

  /**
   * Setter for the old force of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   * @param z_arg new z value
   */
  inline void setOldF(double x_arg, double y_arg, double z_arg) {
    old_f[0] = x_arg;
    old_f[1] = y_arg;
    old_f[2] = z_arg;
  }

  /**
   * Setter for the old force of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   */
  inline void setOldF(double x_arg, double y_arg) {
    old_f[0] = x_arg;
    old_f[1] = y_arg;
  }

  /**
   * Setter the type of the Particle
   * @param pType new type
   */
  inline void setType(int pType) {
    type = pType;
  }

  /**
   * Sets particleType to MOLECULE.
   */
  void setParticleTypeToMolecule() {
    particleType = MOLECULE;
  }

  /**
  * Set stiffness and averageBondLength if particleType is MOLECULE.
  * @param stiffness Stiffness of the Membrane.
  * @param averageBondLength AverageBondLength of the Membrane.
  */
  void setMembraneArguments(double stiffness, double averageBondLength) {
    if (particleType == MOLECULE) {
      membraneArguments.clear();
      membraneArguments.template emplace_back(stiffness);
      membraneArguments.template emplace_back(averageBondLength);
    }
  }

  /**
  * Adds a molecule-pointer to neighbours.
  * @param p molecule-pointer
  */
  void addNeighbour(Particle<dim> *p) {
    if (particleType == MOLECULE) {
      neighbours.emplace_back(p);
    }
  }

  /**
  * Adds a molecule-pointer to diagonalNeighbours.
  * @param p molecule-pointer
  */
  void addDiagonalNeighbour(Particle<dim> *p) {
    if (particleType == MOLECULE) {
      diagonalNeighbours.emplace_back(p);
    }
  }

  /**
   * Checks if the given Particle p is a neighbour.
   * @param p Particle that might be a neighbour
   * @return True if p is a neighbour.
   */
  bool isNeighbour(Particle<dim> *p) {
    if (particleType == MOLECULE)
      return std::find(neighbours.begin(), neighbours.end(), p) != neighbours.end();
    else
      return false;
  }

  /**
   * Checks if the given Particle p is a diagonal neighbour.
   * @param p Particle that might be a diagonal neighbour
   * @return True if p is a diagonal neighbour.
   */
  bool isDiagonalNeighbour(Particle<dim> *p) {
    if (particleType == MOLECULE)
      return std::find(diagonalNeighbours.begin(), diagonalNeighbours.end(), p) != diagonalNeighbours.end();
    else
      return false;
  }

  /**
   * Returns the additionalForces-Vector
   * @return additionalForces
   */
  const std::vector<Force<dim>> &getAdditionalForces() const {
    return additionalForces;
  }

  /**
   * Adds the given force-vector to the additionalForce-Vector.
   * @param additional_forces Additional Force to add to the additionalForce-Vector.
   */
  void addAdditionalForce(const Force<dim> &additional_forces) {
    additionalForces.push_back(additional_forces);
  }

  /**
   * Set fixed to given parameter.
   * @param fix Bool to set fixed to.
   */
  void setFixed(bool fix) {
    fixed = fix;
  }
};
