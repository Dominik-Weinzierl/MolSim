#pragma once

#include <string>
#include "physics/Vector/Vector.h"
#include "logger/Logger.h"

/**
 * Particle is a class that wraps up the properties of a particle, getters, setters and standard methods.
 * @tparam dim dimension of our simulation.
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
   * Type of the particle. Use it for whatever you want
   * (e.g. to separate molecules belonging to different bodies, matters, and so on).
   */
  int type;

 public:

  /**
   * Default constructor.
   * @param type Default value 0.
   */
  explicit Particle(int type_arg) : x{}, v{}, f{}, old_f{}, m{}, type{type_arg} {
    SPDLOG_TRACE("Particle generated");
  }

  /**
   * Copy constructor.
   * @param other Particle to copy.
   */
  Particle(const Particle &other) = default;

  /**
   * Constructor which generates a particle with the given parameters.
   * @param pX Position-Vector.
   * @param pV Velocity-Vector.
   * @param pM Mass.
   * @param type
   */
  Particle(const Vector<dim> &pX, const Vector<dim> &pV, double pM, int pType = 0) : x{pX}, v{pV}, f{}, old_f{}, m{pM},
                                                                                     type{pType} {
    SPDLOG_TRACE("Particle generated");
  }
  /**
   * Default destructor.
   */
  virtual ~Particle() = default;

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
   * Setter for the position of the Particle.
   * @param position new position
   */
  void setX(const Vector<dim> &position) {
    x = position;
  }

  /**
   * Setter for the position of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   * @param z_arg new z value
   */
  void setX(double x_arg, double y_arg, double z_arg) {
    x[0] = x_arg;
    x[1] = y_arg;
    x[2] = z_arg;
  }

  /**
   * Setter for the position of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   */
  void setX(double x_arg, double y_arg) {
    x[0] = x_arg;
    x[1] = y_arg;
  }

  /**
   * Setter for the velocity of the Particle.
   * @param velocity new velocity
   */
  void setV(const Vector<dim> &velocity) {
    v = velocity;
  }

  /**
   * Setter for the velocity of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   * @param z_arg new z value
   */
  void setV(double x_arg, double y_arg, double z_arg) {
    v[0] = x_arg;
    v[1] = y_arg;
    v[2] = z_arg;
  }

  /**
   * Setter for the velocity of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   */
  void setV(double x_arg, double y_arg) {
    v[0] = x_arg;
    v[1] = y_arg;
  }

  /**
   * Setter for the force of the Particle.
   * @param force new force
   */
  void setF(const Vector<dim> &force) {
    f = force;
  }

  /**
   * Setter for the force of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   * @param z_arg new z value
   */
  void setF(double x_arg, double y_arg, double z_arg) {
    f[0] = x_arg;
    f[1] = y_arg;
    f[2] = z_arg;
  }

  /**
   * Setter for the force of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   */
  void setF(double x_arg, double y_arg) {
    f[0] = x_arg;
    f[1] = y_arg;
  }

  /**
   * Setter for the old force of the Particle.
   * @param oldForce new old force
   */
  void setOldF(const Vector<dim> &oldForce) {
    old_f = oldForce;
  }

  /**
   * Setter for the old force of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   * @param z_arg new z value
   */
  void setOldF(double x_arg, double y_arg, double z_arg) {
    old_f[0] = x_arg;
    old_f[1] = y_arg;
    old_f[2] = z_arg;
  }

  /**
   * Setter for the old force of the Particle.
   * @param x_arg new x value
   * @param y_arg new y value
   */
  void setOldF(double x_arg, double y_arg) {
    old_f[0] = x_arg;
    old_f[1] = y_arg;
  }

  /**
   * Methods to update the force.
   * @param x_arg new x value to add
   * @param y_arg new y value to add
   * @param z_arg new z value to add
   */
  void updateForce(double x_arg, double y_arg, double z_arg) {
    f[0] += x_arg;
    f[1] += y_arg;
    f[2] += z_arg;
  }

  /**
   * Methods to update the force.
   * @param x_arg new x value to add
   * @param y_arg new y value to add
   */
  void updateForce(double x_arg, double y_arg) {
    f[0] += x_arg;
    f[1] += y_arg;
  }

  /**
   * Methods to update the force.
   * @param force new force to add
   */
  void updateForce(std::array<double, dim> force) {
    for (size_t i = 0; i < dim; ++i) {
      f[i] += force[i];
    }
  }

  /**
   * Operator which allows the comparison of the particle to a given particle.
   * @param other
   * @return True, if the given Particle equals this Particle.
   */
  bool operator==(const Particle &other) {
    return (x == other.x) and (v == other.v) and (f == other.f) and (type == other.type) and (m == other.m)
        and (old_f == other.old_f);
  }

  /**
   * Method which returns the properties of the particle as a String.
   * @return
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream stream;
    stream << "Particle: X:" << x << " v: " << v << " f: " << f << " old_f: " << old_f << " type: " << type;
    return stream.str();
  }
};

/**
 * Stream operator for Particle(s).
 * @tparam dim dimension of our simulation.
 * @param stream std::ostream
 * @param p Particle to print
 * @return updated stream
 */
template<size_t dim>
std::ostream &operator<<(std::ostream &stream, const Particle<dim> &p) {
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
template<size_t dim>
bool operator==(const Particle<dim> &p1, const Particle<dim> &p2) {
  return p1.getX() == p2.getX() && p1.getV() == p2.getV() && p1.getM() == p2.getM() && p1.getF() == p2.getF()
      && p1.getOldF() == p2.getOldF() && p1.getType() == p2.getType();
}