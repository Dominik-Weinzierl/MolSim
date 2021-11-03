#include <functional>
#include <numeric>
#include <iostream>
#include "Vector.h"
#include "utils/ArrayUtils.h"

//---------------------------Constructor---------------------------
Vector::Vector(double x, double y, double z) : vector{x, y, z} {
  // std::cout << "Vector constructed!" << std::endl;
}

Vector::Vector(std::array<double, 3> &vector) : vector{vector} {
  // std::cout << "Vector constructed!" << std::endl;
}

Vector::Vector() : vector({0, 0, 0}) {
  // std::cout << "Vector constructed!" << std::endl;
}

Vector::~Vector() {
  // std::cout << "Vector destructed!" << std::endl;
}

//---------------------------Operators---------------------------
Vector &Vector::operator+=(const Vector &other) {
  std::transform(this->begin(), this->end(), other.begin(), this->begin(), [](auto l, auto r) {
    return l + r;
  });
  return *this;
};

Vector operator+(Vector lhs, const Vector &rhs) {
  lhs += rhs;
  return lhs;
}

Vector &Vector::operator-=(const Vector &other) {
  std::transform(this->begin(), this->end(), other.begin(), this->begin(), [](auto l, auto r) {
    return l - r;
  });
  return *this;
};

Vector operator-(Vector lhs, const Vector &rhs) {
  lhs -= rhs;
  return lhs;
};

Vector &Vector::operator-() {
  std::transform(begin(), end(), begin(), [](auto l) {
    return -l;
  });
  return *this;
}

// Scalar product
double Vector::operator*(const Vector &other) const {
  return std::inner_product(std::begin(vector), std::end(vector), std::begin(other.vector), 0.0);
};

// Scaling of vectors
Vector operator*(Vector lhs, const double &rhs) {
  lhs *= rhs;
  return lhs;
};

Vector operator*(const double &rhs, Vector lhs) {
  lhs *= rhs;
  return lhs;
};

Vector &Vector::operator*=(double d) {
  std::transform(this->begin(), this->end(), this->begin(), [&](auto v) {
    return v * d;
  });
  return *this;
};

Vector operator/(Vector lhs, const double &rhs) {
  lhs /= rhs;
  return lhs;
}

Vector &Vector::operator/=(double d) {
  std::transform(this->begin(), this->end(), this->begin(), [&](auto v) {
    return v / d;
  });
  return *this;
};

double &Vector::operator[](unsigned long i) {
  return vector[i];
};

double Vector::operator[](unsigned long i) const {
  return vector[i];
};

bool Vector::operator==(const Vector &other) const {
  return vector == other.vector;
}

//---------------------------Getter & Setter---------------------------
const std::array<double, 3> &Vector::get() const {
  return vector;
};

//---------------------------Methods---------------------------

size_t Vector::size() {
  return 3;
}

std::string Vector::toString() const {
  return "x: " + ArrayUtils::to_string(vector);
}

std::ostream &operator<<(std::ostream &stream, const Vector &v) {
  stream << v.toString();
  return stream;
}
