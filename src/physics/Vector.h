#pragma once

#include <array>
#include <ostream>

class Vector {
 private:
  std::array<double, 3> vector{};
  int length = 3;

 public:
  static double euclideanNorm(const Vector &i, const Vector &j);

  Vector() = default;
  Vector(double x, double y, double z);
  explicit Vector(std::array<double, 3> &vector);
  virtual ~Vector() = default;

  Vector operator+(const Vector &other) const;
  Vector &operator+=(const Vector &other);
  Vector operator-(const Vector &other) const;
  Vector &operator-=(const Vector &other);
  double operator*(const Vector &other) const;
  Vector &operator*=(double d);
  Vector operator*(double d) const;
  double operator[](int i) const;

  [[nodiscard]] const std::array<double, 3> &getVector() const;

  void setX(double x);
  void setY(double y);
  void setZ(double z);

  [[nodiscard]] std::string toString() const;

  [[nodiscard]] const double *begin() const{ return vector.begin(); }
  [[nodiscard]] const double *end() const{ return vector.end(); }
  [[nodiscard]] size_t size() const;
};

// Implemented in "utils/ArrayUtils.h"
std::ostream &operator<<(std::ostream &stream, const Vector &v);
Vector operator*(double value, const Vector &v);