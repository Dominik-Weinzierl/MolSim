#pragma once

#include "spdlog/spdlog.h"

#include <array>
#include <ostream>
#include <numeric>
#include <utils/ArrayUtils.h>

template<size_t dim> using Vector = std::array<double, dim>;

template<size_t dim>
Vector<dim> operator+(Vector<dim> lhs, const Vector<dim> &rhs) {
  SPDLOG_TRACE("Calculating {0} + {1}", lhs, rhs);
  std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), [](auto l, auto r) {
    return l + r;
  });
  return lhs;
}

template<size_t dim>
Vector<dim> operator-(Vector<dim> lhs, const Vector<dim> &rhs) {
  SPDLOG_TRACE("Calculating {0} - {1}", lhs, rhs);
  std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), [](auto l, auto r) {
    return l - r;
  });
  return lhs;
}

/**
 * Operator that allows scalar multiplication on a given Vector.
 * @param lhs Vector.
 * @param rhs Double to scale the vector.
 * @return
 */
template<size_t dim>
double operator*(const Vector<dim> &lhs, const Vector<dim> &rhs) {
  SPDLOG_TRACE("Calculating {0} * {1}", lhs, rhs);
  return std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), 0.0);
}

/**
 * Operator that allows scalar multiplication on a given Vector.
 * @param rhs Double to scale the vector.
 * @param lhs Vector.
 * @return
 */
template<size_t dim>
Vector<dim> operator*(Vector<dim> lhs, const double &d) {
  SPDLOG_TRACE("Calculating {0} * {1}", lhs, d);
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [&](auto v) {
    return v * d;
  });
  return lhs;
}

/**
 * Operator that allows scalar multiplication on a given Vector.
 * @param rhs Double to scale the vector.
 * @param lhs Vector.
 * @return
 */
template<size_t dim>
Vector<dim> operator*(const double &d, Vector<dim> lhs) {
  SPDLOG_TRACE("Calculating {0} * {1}", lhs, d);
  return lhs * d;
}

template<size_t dim>
Vector<dim> operator/(Vector<dim> lhs, const double &d) {
  SPDLOG_TRACE("Calculating {0} / {1}", lhs, d);
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [&](auto v) {
    return v / d;
  });
  return lhs;
}

template<size_t dim>
std::ostream &operator<<(std::ostream &stream, const Vector<dim> &v) {
  stream << ArrayUtils::to_string(v);
  return stream;
}

