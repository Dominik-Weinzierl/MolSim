#pragma once

#include <string>
#include "physics/Vector/Vector.h"

//! Particle is a class that wraps up the properties of a particle, getters, setters and standard methods.
class Particle {
 private:
  //! Position of the particle
  Vector x;

  //! Velocity of the particle
  Vector v;

  //! Force effective on this particle
  Vector f;

  //! Force which was effective on this particle
  Vector old_f;

  //! Mass of this particle
  double m;

  //! Type of the particle. Use it for whatever you want (e.g. to separate
  //! molecules belonging to different bodies, matters, and so on)
  int type;

 public:
  //! Default constructor
  explicit Particle(int type = 0);

  //! Copy constructor
  Particle(const Particle &other);

  //! Constructor which generates a particle with the given parameters
  Particle(const Vector &x_arg, const Vector &v_arg, double m_arg, int type = 0);

  //! Default destructor
  virtual ~Particle();

  //! Returns the position, velocity, force, old force, mass or type of the particle
  [[nodiscard]] const Vector &getX() const;
  [[nodiscard]] const Vector &getV() const;
  [[nodiscard]] const Vector &getF() const;
  [[nodiscard]] const Vector &getOldF() const;
  [[nodiscard]] double getM() const;
  [[nodiscard]] int getType() const;

  //! Sets the position, velocity, force or old force of the particle
  void setX(const Vector &position);
  void setV(const Vector &velocity);
  void setF(const Vector &force);
  void setOldF(const Vector &oldForce);

  void updateForce(const Vector &force);

  //! Operator which allows the comparison of the particle to a given particle
  bool operator==(Particle &other);

  //! Method which returns the properties of the particle as a String
  [[nodiscard]] std::string toString() const;
};