#pragma once

#include <string>
#include "physics/Vector.h"

class Particle {

private:
  /**
   * Position of the particle
   */
  Vector x;

  /**
   * Velocity of the particle
   */
  Vector v;

  /**
   * Force effective on this particle
   */
  Vector f;

  /**
   * Force which was effective on this particle
   */
  Vector old_f;

  /**
   * Mass of this particle
   */
  double m{};

  /**
   * Type of the particle. Use it for whatever you want (e.g. to separate
   * molecules belonging to different bodies, matters, and so on)
   */
  int type;

public:
  explicit Particle(int type = 0);

  Particle(const Particle &other);

  Particle(
      // for visualization, we always need 3 coordinates
      // -> in case of 2d, we use only the first and the second
      const Vector& x_arg, const Vector& v_arg, double m_arg,
      int type = 0);

  virtual ~Particle();

  [[nodiscard]] const Vector &getX() const;

  [[nodiscard]] const Vector &getV() const;

  [[nodiscard]] const Vector &getF() const;

  [[nodiscard]] const Vector &getOldF() const;

  [[nodiscard]] double getM() const;

  [[nodiscard]] int getType() const;

  void setX(const Vector& position);

  void setV(const Vector& velocity);

  void setF(const Vector& force);

  void setOldF(const Vector& oldForce);

  bool operator==(Particle &other);

  [[nodiscard]] std::string toString() const;
};

std::ostream &operator<<(std::ostream &stream, Particle &p);
