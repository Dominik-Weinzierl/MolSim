#include <functional>
#include <numeric>
#include <iostream>
#include <spdlog/spdlog.h>
#include "Vector.h"
#include "utils/ArrayUtils.h"

//---------------------------Constructor---------------------------
Vector::Vector(double x, double y, double z) : vector{x, y, z} {
  //SPDLOG_INFO("Vector generated");
}

Vector::Vector(std::array<double, 3> &vector) : vector{vector} {
  //SPDLOG_INFO("Vector generated by copy");
}

Vector::Vector() : vector({0, 0, 0}) {
  //SPDLOG_INFO("Vector generated");
}

Vector::~Vector() {
  //SPDLOG_INFO("Vector destructed");
}

//---------------------------Operators---------------------------
Vector &Vector::operator+=(const Vector &other) {
  SPDLOG_DEBUG("Calculating {0} + {1}", this, other);
  std::transform(this->begin(), this->end(), other.begin(), this->begin(), [](auto l, auto r) {
    return l + r;
  });
  return *this;
};

Vector operator+(Vector lhs, const Vector &rhs) {
  SPDLOG_DEBUG("Calculating {0} + {1}", lhs, rhs);
  lhs += rhs;
  return lhs;
}

Vector &Vector::operator-=(const Vector &other) {
  SPDLOG_DEBUG("Calculating {0} - {1}", this, other);
  std::transform(this->begin(), this->end(), other.begin(), this->begin(), [](auto l, auto r) {
    return l - r;
  });
  return *this;
};

Vector operator-(Vector lhs, const Vector &rhs) {
  SPDLOG_DEBUG("Calculating {0} - {1}", lhs, rhs);
  lhs -= rhs;
  return lhs;
};

Vector &Vector::operator-() {
  SPDLOG_DEBUG("Calculating -{}", this);
  std::transform(begin(), end(), begin(), [](auto l) {
    return -l;
  });
  return *this;
}

// Scalar product
double Vector::operator*(const Vector &other) const {
  SPDLOG_DEBUG("Calculating {0} * {1}", this, other);
  return std::inner_product(std::begin(vector), std::end(vector), std::begin(other.vector), 0.0);
};

// Scaling of vectors
Vector operator*(Vector lhs, const double &rhs) {
  SPDLOG_DEBUG("Calculating {0} * {1}", lhs, rhs);
  lhs *= rhs;
  return lhs;
};

Vector operator*(const double &rhs, Vector lhs) {
  SPDLOG_DEBUG("Calculating {0} * {1}", rhs, lhs);
  lhs *= rhs;
  return lhs;
};

Vector &Vector::operator*=(double d) {
  SPDLOG_DEBUG("Calculating {0} * {1}", this, d);
  std::transform(this->begin(), this->end(), this->begin(), [&](auto v) {
    return v * d;
  });
  return *this;
};

Vector operator/(Vector lhs, const double &rhs) {
  SPDLOG_DEBUG("Calculating {0} / {1}", lhs, rhs);
  lhs /= rhs;
  return lhs;
}

Vector &Vector::operator/=(double d) {
  SPDLOG_DEBUG("Calculating {0} / {1}", this, d);
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
