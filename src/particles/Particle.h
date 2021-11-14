#pragma once

#include <string>
#include "physics/Vector/Vector.h"

/**
 * Particle is a class that wraps up the properties of a particle, getters, setters and standard methods.
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

  [[nodiscard]] const Vector<dim> &getX() const {
    return x;
  }

  [[nodiscard]] const Vector<dim> &getV() const {
    return v;
  }

  [[nodiscard]] const Vector<dim> &getF() const {
    return f;
  }

  [[nodiscard]] const Vector<dim> &getOldF() const {
    return old_f;
  }

  [[nodiscard]] const double &getM() const {
    return m;
  }

  [[nodiscard]] int getType() const {
    return type;
  }

  void setX(const Vector<dim> &position) {
    x = position;
  }

  void setX(double x_arg, double y_arg, double z_arg) {
    x[0] = x_arg;
    x[1] = y_arg;
    x[2] = z_arg;
  }

  void setX(double x_arg, double y_arg) {
    x[0] = x_arg;
    x[1] = y_arg;
  }

  void setV(const Vector<dim> &velocity) {
    v = velocity;
  }

  void setV(double x_arg, double y_arg, double z_arg) {
    v[0] = x_arg;
    v[1] = y_arg;
    v[2] = z_arg;
  }

  void setV(double x_arg, double y_arg) {
    v[0] = x_arg;
    v[1] = y_arg;
  }

  void setF(const Vector<dim> &force) {
    f = force;
  }

  void setF(double x_arg, double y_arg, double z_arg) {
    f[0] = x_arg;
    f[1] = y_arg;
    f[2] = z_arg;
  }

  void setF(double x_arg, double y_arg) {
    f[0] = x_arg;
    f[1] = y_arg;
  }

  void setOldF(const Vector<dim> &oldForce) {
    old_f = oldForce;
  }

  void setOldF(double x_arg, double y_arg, double z_arg) {
    old_f[0] = x_arg;
    old_f[1] = y_arg;
    old_f[2] = z_arg;
  }

  void setOldF(double x_arg, double y_arg) {
    old_f[0] = x_arg;
    old_f[1] = y_arg;
  }

  void updateForce(double x_arg, double y_arg, double z_arg) {
    f[0] += x_arg;
    f[1] += y_arg;
    f[2] += z_arg;
  }

  void updateForce(double x_arg, double y_arg) {
    f[0] += x_arg;
    f[1] += y_arg;
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

template<size_t dim>
std::ostream &operator<<(std::ostream &stream, const Particle<dim> &p) {
  stream << p.toString();
  return stream;
}