#pragma once

#include <array>
#include <ostream>

class Vector {

 private:
  std::array<double, 3> vector{};

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

};

std::ostream &operator<<(std::ostream &stream, const Vector &v);
