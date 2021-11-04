#pragma once

#include <array>
#include <ostream>

/**
 * The Vector class renames a double-array of length 3 and rewrites operators to fit the datastructure.
 */
class Vector {
 private:

  /**
   * Defines a double-array of length 3 called vector.
   */
  std::array<double, 3> vector{};

 public:
  Vector(double x, double y, double z);

  Vector(const Vector &other) = default;

  Vector();

  explicit Vector(std::array<double, 3> &vector);

  virtual ~Vector();

  Vector &operator=(const Vector &other) = default;

  Vector &operator+=(const Vector &other);

  Vector &operator-=(const Vector &other);

  Vector &operator-();

  /**
   * Operator that allows scalar multiplication on vectors.
   * @param d Double to scale the vector.
   * @return
   */
  Vector &operator*=(double d);

  Vector &operator/=(double d);

  /**
   * Operator that allows the scalar product on vectors.
   * @param other Second Vector for the scalar product.
   * @return
   */
  double operator*(const Vector &other) const;

  /**
   * Operator that allows mutable member access.
   * @param i Index for member access.
   * @return
   */
  double &operator[](unsigned long i);

  /**
   * Operator that allows immutable member access.
   * @param i Index for member access.
   * @return
   */
  double operator[](unsigned long i) const;

  /**
   * Operator that allows the comparison.
   * @param other Vector for comparison.
   * @return
   */
  bool operator==(const Vector &other) const;

  friend Vector operator+(Vector lhs, const Vector &rhs);

  friend Vector operator-(Vector lhs, const Vector &rhs);

  /**
   * Operator that allows scalar multiplication on a given Vector.
   * @param lhs Vector.
   * @param rhs Double to scale the vector.
   * @return
   */
  friend Vector operator*(Vector lhs, const double &rhs);

  /**
   * Operator that allows scalar multiplication on a given Vector.
   * @param rhs Double to scale the vector.
   * @param lhs Vector.
   * @return
   */
  friend Vector operator*(const double &rhs, Vector lhs);

  friend Vector operator/(Vector lhs, const double &rhs);

  friend std::ostream &operator<<(std::ostream &stream, const Vector &v);

  [[nodiscard]] const std::array<double, 3> &get() const;

  [[nodiscard]] std::string toString() const;

  /**
   * @return Mutable Iterator to the beginning of the particles-Vector.
   */
  [[nodiscard]] auto begin() { return vector.begin(); }

  /**
   * @return Imutable Iterator to the end of the particles-Vector.
   */
  [[nodiscard]] auto end() { return vector.end(); }

  /**
   * @return Immutable Iterator to the beginning of the particles-Vector.
   */
  [[nodiscard]] auto begin() const { return vector.begin(); }

  /**
   * @return Immutable Iterator to the end of the particles-Vector.
   */
  [[nodiscard]] auto end() const { return vector.end(); }

  /**
   * @return Size of the Vector.
   */
  [[nodiscard]] static unsigned long size();
};
