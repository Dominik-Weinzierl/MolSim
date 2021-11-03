#pragma once

#include <array>
#include <ostream>

//! The Vector class renames a double-array of length 3 and rewrites operators to fit the datastructure
class Vector {
 private:
  //! Defines a double-array of length 3 called vector
  std::array<double, 3> vector{};
 public:
  Vector(double x, double y, double z);
  Vector(const Vector &other) = default;
  Vector();
  explicit Vector(std::array<double, 3> &vector);
  virtual ~Vector();

  //! Operators that allow basic arithmetic operations on vectors and the setting of members
  Vector &operator=(const Vector &other) = default;
  Vector &operator+=(const Vector &other);
  Vector &operator-=(const Vector &other);
  Vector &operator-();
  //! Scalar multiplication
  Vector &operator*=(double d);
  Vector &operator/=(double d);
  //! Cross Product
  double operator*(const Vector &other) const;
  //! Member access
  double &operator[](unsigned long i);
  double operator[](unsigned long i) const;
  //! Comparision
  bool operator==(const Vector &other) const;

  friend Vector operator+(Vector lhs, const Vector &rhs);
  friend Vector operator-(Vector lhs, const Vector &rhs);
  //! Scalar multiplication
  friend Vector operator*(Vector lhs, const double &rhs);
  friend Vector operator*(const double &rhs, Vector lhs);
  friend Vector operator/(Vector lhs, const double &rhs);
  friend std::ostream &operator<<(std::ostream &stream, const Vector &v);

  //! Basic getter that returns the vector
  [[nodiscard]] const std::array<double, 3> &get() const;

  [[nodiscard]] std::string toString() const;

  //! Methods that return the size and allow access to the begin and end of a vector
  [[nodiscard]] auto begin() { return vector.begin(); }
  [[nodiscard]] auto end() { return vector.end(); }
  [[nodiscard]] auto begin() const { return vector.begin(); }
  [[nodiscard]] auto end() const { return vector.end(); }
  [[nodiscard]] static unsigned long size();
};
