#pragma once

#include <array>
#include <ostream>

class Vector {
 private:
  std::array<double, 3> vector{};
 public:

  Vector(double x, double y, double z);
  Vector(const Vector &other) = default;
  Vector();
  explicit Vector(std::array<double, 3> &vector);
  virtual ~Vector() = default;

  Vector &operator=(const Vector &other) = default;
  Vector &operator+=(const Vector &other);
  Vector &operator-=(const Vector &other);
  Vector &operator*=(double d);
  Vector &operator/=(double d);
  double operator*(const Vector &other) const;
  double operator[](unsigned long i) const;
  bool operator==(const Vector &other) const;

  friend Vector operator+(Vector lhs, const Vector &rhs);
  friend Vector operator-(Vector lhs, const Vector &rhs);
  friend Vector operator*(Vector lhs, const double &rhs);
  friend Vector operator*(const double &rhs, Vector lhs);
  friend Vector operator/(Vector lhs, const double &rhs);
  friend std::ostream &operator<<(std::ostream &stream, const Vector &v);

  [[nodiscard]] const std::array<double, 3> &get() const;

  [[nodiscard]] std::string toString() const;

  [[nodiscard]] auto begin() { return vector.begin(); }
  [[nodiscard]] auto end() { return vector.end(); }
  [[nodiscard]] auto begin() const { return vector.begin(); }
  [[nodiscard]] auto end() const { return vector.end(); }
  [[nodiscard]] static unsigned long size();
};
