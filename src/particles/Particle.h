#pragma once

#include <string>
#include "physics/Vector/Vector.h"

/**
 * Particle is a class that wraps up the properties of a particle, getters, setters and standard methods.
 */
class Particle {
 private:

  /**
   * Position of the particle.
   */
  Vector x;

  /**
   * Velocity of the particle.
   */
  Vector v;

  /**
   * Force effective on this particle.
   */
  Vector f;

  /**
   * Force which was effective on this particle.
   */
  Vector old_f;

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
  explicit Particle(int type = 0);

  /**
   * Copy constructor.
   * @param other Particle to copy.
   */
  Particle(const Particle &other) = default;

  /**
   * Constructor which generates a particle with the given parameters.
   * @param x_arg Position-Vector.
   * @param v_arg Velocity-Vector.
   * @param m_arg Mass.
   * @param type
   */
  Particle(const Vector &x_arg, const Vector &v_arg, double m_arg, int type = 0);

  /**
   * Default destructor.
   */
  virtual ~Particle() = default;

  [[nodiscard]] const Vector &getX() const;

  [[nodiscard]] const Vector &getV() const;

  [[nodiscard]] const Vector &getF() const;

  [[nodiscard]] const Vector &getOldF() const;

  [[nodiscard]] const double& getM() const;

  [[nodiscard]] int getType() const;

  void setX(const Vector &position);

  void setX(double x_arg, double y_arg, double z_arg);

  void setV(const Vector &velocity);

  void setV(double x_arg, double y_arg, double z_arg);

  void setF(const Vector &force);

  void setF(double x_arg, double y_arg, double z_arg);

  void setOldF(const Vector &oldForce);

  void setOldF(double x_arg, double y_arg, double z_arg);

  /**
   * Adds given force to current force of the Particle.
   * @param force
   */
  void updateForce(const Vector &force);

  void updateForce(double x_arg, double y_arg, double z_arg);

  /**
   * Operator which allows the comparison of the particle to a given particle.
   * @param other
   * @return True, if the given Particle equals this Particle.
   */
  bool operator==(const Particle &other);

  /**
   * Method which returns the properties of the particle as a String.
   * @return
   */
  [[nodiscard]] std::string toString() const;
};