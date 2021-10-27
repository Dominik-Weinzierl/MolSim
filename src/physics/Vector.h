#pragma once

#include <array>
#include <ostream>

class Vector{

 private:
  std::array<double, 3> vector{};

 public:

  //TODO: getDistance with euclidianNorm, operators -, scalar-multiplication, *
  static double getDistance(const Vector& i, const Vector& j);
  static double euclidianNorm(const Vector& i, const Vector& j);

  Vector() = default;
  Vector(double x, double y, double z);
  explicit Vector(std::array<double, 3> &vector);
  virtual ~Vector() = default;

  Vector operator+(Vector& other);
  Vector operator-(const Vector& other);
  Vector operator*(Vector& other);
  Vector operator*(double d);
  double operator[](int i);
  std::ostream& operator<<(std::ostream& os) const;

  [[nodiscard]] const std::array<double, 3> &getVector() const;

  void setX(double x);
  void setY(double y);
  void setZ(double z);

  [[nodiscard]] std::string toString() const;

};
