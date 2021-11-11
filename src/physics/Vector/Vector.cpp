#include <functional>
#include <numeric>
#include <iostream>
#include <spdlog/spdlog.h>
#include "Vector.h"
#include "utils/ArrayUtils.h"

Vector operator+(Vector lhs, const Vector &rhs) {
  // SPDLOG_DEBUG("Calculating {0} + {1}", lhs, rhs);
  std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), [](auto l, auto r) {
    return l + r;
  });
  return lhs;
}

Vector operator-(Vector lhs, const Vector &rhs) {
  // SPDLOG_DEBUG("Calculating {0} - {1}", lhs, rhs);
  std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), [](auto l, auto r) {
    return l - r;
  });
  return lhs;
}

// Scalar product
double operator*(const Vector &lhs, const Vector &rhs) {
  // SPDLOG_DEBUG("Calculating {0} * {1}", this, other);
  return std::inner_product(lhs.begin(), lhs.begin(), rhs.begin(), 0.0);
}

// Scaling of vectors
Vector operator*(Vector lhs, const double &d) {
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [&](auto v) {
    return v * d;
  });
  return lhs;
}

Vector operator*(const double &d, Vector lhs) {
  // SPDLOG_DEBUG("Calculating {0} * {1}", rhs, lhs);
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [&](auto v) {
    return v * d;
  });
  return lhs;
}

Vector operator/(Vector lhs, const double &d) {
  // SPDLOG_DEBUG("Calculating {0} / {1}", lhs, rhs);
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [&](auto v) {
    return v * d;
  });
  return lhs;
}

//---------------------------Methods---------------------------

std::ostream &operator<<(std::ostream &stream, const Vector &v) {
  stream << ArrayUtils::to_string(v);
  return stream;
}
