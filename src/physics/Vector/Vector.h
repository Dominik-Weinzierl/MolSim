#pragma once

#include <array>
#include <ostream>

typedef std::array<double, 3> Vector;

Vector operator+(Vector lhs, const Vector &rhs);

Vector operator-(Vector lhs, const Vector &rhs);

/**
 * Operator that allows scalar multiplication on a given Vector.
 * @param lhs Vector.
 * @param rhs Double to scale the vector.
 * @return
 */
Vector operator*(Vector lhs, const double &d);

/**
 * Operator that allows scalar multiplication on a given Vector.
 * @param rhs Double to scale the vector.
 * @param lhs Vector.
 * @return
 */
Vector operator*(const double &d, Vector lhs);

double operator*(const Vector& lhs, const Vector& rhs);

Vector operator/(Vector lhs, const double &d);

std::ostream &operator<<(std::ostream &stream, const Vector &v);

