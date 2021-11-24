#pragma once

#include "logger/Logger.h"

#include <array>
#include <ostream>
#include <numeric>
#include <utils/ArrayUtils.h>

/**
 * Alias for std::array<double, dim>.
 */
template<size_t dim> using Vector = std::array<double, dim>;

/**
 * Add two Vector(s).
 * @tparam dim dimension of our simulation.
 * @param lhs first vector as value (used for better chaining)
 * @param rhs second vector as reference (used for better chaining)
 * @return updated first vector
 */
template<size_t dim>
Vector<dim> operator+(Vector<dim> lhs, const Vector<dim> &rhs) {
  SPDLOG_TRACE("Calculating {0} + {1}", ArrayUtils::to_string(lhs), ArrayUtils::to_string(rhs));
  std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), [](auto l, auto r) {
    return l + r;
  });
  return lhs;
}

/**
 * Subtract two Vector(s)
 * @tparam dim dimension of our simulation.
 * @param lhs first vector as value (used for better chaining)
 * @param rhs second vector as reference (used for better chaining)
 * @return updated first vector
 */
template<size_t dim>
Vector<dim> operator-(Vector<dim> lhs, const Vector<dim> &rhs) {
  SPDLOG_TRACE("Calculating {0} - {1}", ArrayUtils::to_string(lhs), ArrayUtils::to_string(rhs));
  std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), [](auto l, auto r) {
    return l - r;
  });
  return lhs;
}

/**
 * Invert Vector
 * @tparam dim dimension of our simulation.
 * @param lhs first vector as value (used for better chaining)
 * @return inverted vector
 */
template<size_t dim>
Vector<dim> &operator-(Vector<dim> &lhs) {
  SPDLOG_TRACE("Calculating -{0}" ArrayUtils::to_string(lhs));
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [](auto v) {
    return -v;
  });
  return lhs;
}

/**
 * Operator that allows scalar multiplication on a given Vector.
 * @tparam dim dimension of our simulation.
 * @param lhs first vector as reference
 * @param rhs second vector as reference
 * @return result of scalar multiplication
 */
template<size_t dim>
double operator*(const Vector<dim> &lhs, const Vector<dim> &rhs) {
  SPDLOG_TRACE("Calculating {0} * {1}", ArrayUtils::to_string(lhs), ArrayUtils::to_string(rhs));
  return std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), 0.0);
}

/**
 * Operator used to scale a vector.
 * @tparam dim dimension of our simulation.
 * @param d double to scale the vector.
 * @param lhs vector as value (used for better chaining)
 * @return scaled vector
 */
template<size_t dim>
Vector<dim> operator*(Vector<dim> lhs, const double &d) {
  SPDLOG_TRACE("Calculating {0} * {1}", ArrayUtils::to_string(lhs), d);
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [&](auto v) {
    return v * d;
  });
  return lhs;
}

/**
 * Operator used to scale a vector.
 * @tparam dim dimension of our simulation.
 * @param d double to scale the vector.
 * @param lhs vector as value (used for better chaining)
 * @return scaled vector
 */
template<size_t dim>
Vector<dim> operator*(const double &d, Vector<dim> lhs) {
  SPDLOG_TRACE("Calculating {0} * {1}", ArrayUtils::to_string(lhs), d);
  return lhs * d;
}

/**
 * Operator used to scale a vector by division.
 * @tparam dim dimension of our simulation.
 * @param d double to scale the vector.
 * @param lhs vector as value (used for better chaining)
 * @return scaled vector
 */
template<size_t dim>
Vector<dim> operator/(Vector<dim> lhs, const double &d) {
  SPDLOG_TRACE("Calculating {0} / {1}", ArrayUtils::to_string(lhs), d);
  std::transform(lhs.begin(), lhs.end(), lhs.begin(), [&](auto v) {
    return v / d;
  });
  return lhs;
}

/**
 *
 * @tparam dim dimension of our simulation.
 * @param stream std::ostream
 * @param v Vector to print
 * @return updated stream
 */
template<size_t dim>
std::ostream &operator<<(std::ostream &stream, const Vector<dim> &v) {
  stream << ArrayUtils::to_string(v);
  return stream;
}

