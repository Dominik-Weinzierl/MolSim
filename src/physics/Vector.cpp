#include <functional>
#include <numeric>
#include <complex>
#include "Vector.h"
#include "utils/ArrayUtils.h"

//---------------------------Constructor---------------------------
Vector::Vector(double x, double y, double z) : vector{x, y, z} {}
Vector::Vector(std::array<double, 3> &vector) : vector{vector} {}

//---------------------------Operators---------------------------
Vector Vector::operator+(const Vector &other) const {
  auto vec = ArrayUtils::elementWisePairOp(vector, other.vector, std::plus<>());
  return Vector(vec);
}

Vector &Vector::operator+=(const Vector &other) {
  for (auto i = 0; i < length; ++i) {
    vector[i] += other[i];
  }
  return *this;
};

Vector Vector::operator-(const Vector &other) const {
  auto vec = ArrayUtils::elementWisePairOp(vector, other.vector, std::minus<>());
  return Vector(vec);
};

Vector &Vector::operator-=(const Vector &other) {
  for (int i = 0; i < length; ++i) {
    vector[i] -= other[i];
  }
  return *this;
};

// Scalar product
double Vector::operator*(const Vector &other) const {
  return std::inner_product(std::begin(vector), std::end(vector), std::begin(other.vector), 0.0);
};

// Scaling of vectors
Vector Vector::operator*(double d) const {
  auto vec = ArrayUtils::elementWiseScalarOp(d, vector, std::multiplies());
  return Vector(vec);
};

Vector operator*(double value, const Vector &v) {
  return v * value;
}

// Scaling of vectors
Vector &Vector::operator*=(double d) {
  for (double &i: vector) {
    i *= d;
  }
  return *this;
};

double Vector::operator[](int i) const {
  return vector[i];
};

bool Vector::operator==(const Vector &other) const {
  return vector == other.vector;
}

//---------------------------Getter & Setter---------------------------
const std::array<double, 3> &Vector::getVector() const {
  return vector;
};

void Vector::setX(double x) {
  vector[0] = x;
};

void Vector::setY(double y) {
  vector[1] = y;
};

void Vector::setZ(double z) {
  vector[2] = z;
}

//---------------------------Methods---------------------------
double Vector::euclideanNorm(const Vector &i, const Vector &j) {
  double sum = 0;
  for (int t = 0; t < i.length; ++t) {
    sum += std::pow((i[t] - j[t]), 2);
  }
  return std::sqrt(sum);
}

size_t Vector::size() const {
  return length;
}

std::string Vector::toString() const {
  return "x: " + ArrayUtils::to_string(vector);
}

std::ostream &operator<<(std::ostream &stream, const Vector &v) {
  stream << v.toString();
  return stream;
}

