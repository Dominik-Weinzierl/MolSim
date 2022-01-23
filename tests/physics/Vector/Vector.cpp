#include <gtest/gtest.h>

#include "physics/Vector/Vector.h"

/**
 * ************************************************
 * Test correct functionality of the class Vector.
 * ******************************************+*****
 */

/**
 * Test correctness of constructors of class Vector.
 */
TEST(Vector_3D, constructor) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Test with default constructor
  Vector<dim> v1{};
  EXPECT_DOUBLE_EQ(v1[0], 0.0);
  EXPECT_DOUBLE_EQ(v1[1], 0.0);
  EXPECT_DOUBLE_EQ(v1[2], 0.0);

  // Test with constructor which takes three doubles as argument.
  Vector<dim> v2{1.0, 2.0, 3.0};
  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);
  EXPECT_DOUBLE_EQ(v2[2], 3.0);

  // Test with constructor which takes a std::array as argument.
  std::array<double, dim> arr{1.0, 2.0, 3.0};
  Vector<dim> v3{arr};
  EXPECT_DOUBLE_EQ(v3[0], 1.0);
  EXPECT_DOUBLE_EQ(v3[1], 2.0);
  EXPECT_DOUBLE_EQ(v3[2], 3.0);
}

/**
 * Test correctness of copy assignment operator of class Vector.
 */
TEST(Vector_3D, copy_assignment) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Copy Vector v1
  Vector<dim> v1{1.0, 2.0, 3.0};
  Vector<dim> v2 = v1;

  // Change value of v1 and test if v2 is unchanged
  v1[0] = 5.0;
  EXPECT_DOUBLE_EQ(v2[0], 1.0);
}

/**
 * Test correctness of `operator*` of class Vector.
 */
TEST(Vector_3D, operatorMultiplicationOne) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0, 3.0};
  Vector<dim> v2{1.0, 2.0, 3.0};


  // Scalar product
  double scalarProduct = v1 * v2;

  // Check if v1 and v2 are unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);
  EXPECT_DOUBLE_EQ(v1[2], 3.0);

  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);
  EXPECT_DOUBLE_EQ(v2[2], 3.0);

  // Test values of v2
  EXPECT_DOUBLE_EQ(scalarProduct, 14);
}

/**
 * Test correctness of `operator+` of class Vector.
 */
TEST(Vector_3D, operatorAddition) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0, 3.0};
  Vector<dim> v2{1.0, 2.0, 3.0};

  Vector<dim> result = v1 + v2;

  // Check if v1 and v2 are unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);
  EXPECT_DOUBLE_EQ(v1[2], 3.0);

  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);
  EXPECT_DOUBLE_EQ(v2[2], 3.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 2.0);
  EXPECT_DOUBLE_EQ(result[1], 4.0);
  EXPECT_DOUBLE_EQ(result[2], 6.0);
}

/**
 * Test correctness of `operator-` of class Vector.
 */
TEST(Vector_3D, operatorSubtraction) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0, 3.0};
  Vector<dim> v2{1.0, 2.0, 3.0};

  Vector<dim> result = v1 - v2;

  // Check if v1 and v2 are unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);
  EXPECT_DOUBLE_EQ(v1[2], 3.0);

  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);
  EXPECT_DOUBLE_EQ(v2[2], 3.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 0.0);
  EXPECT_DOUBLE_EQ(result[1], 0.0);
  EXPECT_DOUBLE_EQ(result[2], 0.0);
}

/**
 * Test correctness of `operator*` of class Vector.
 */
TEST(Vector_3D, operatorMultiplicationTwo) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0, 3.0};
  double factor = 2.0;

  Vector<dim> result = v1 * factor;

  // Check if v1 is unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);
  EXPECT_DOUBLE_EQ(v1[2], 3.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 2.0);
  EXPECT_DOUBLE_EQ(result[1], 4.0);
  EXPECT_DOUBLE_EQ(result[2], 6.0);

  result = factor * v1;

  // Check if v1 is unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);
  EXPECT_DOUBLE_EQ(v1[2], 3.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 2.0);
  EXPECT_DOUBLE_EQ(result[1], 4.0);
  EXPECT_DOUBLE_EQ(result[2], 6.0);
}

/**
 * Test correctness of `operator/` of class Vector.
 */
TEST(Vector_3D, operatorDivision) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0, 3.0};
  double factor = 2.0;

  Vector<dim> result = v1 / factor;

  // Check if v1 is unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);
  EXPECT_DOUBLE_EQ(v1[2], 3.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 0.5);
  EXPECT_DOUBLE_EQ(result[1], 1.0);
  EXPECT_DOUBLE_EQ(result[2], 1.5);
}

/**
 * Test correctness of constructors of class Vector.
 */
TEST(Vector_2D, constructor) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Test with default constructor
  Vector<dim> v1{};
  EXPECT_DOUBLE_EQ(v1[0], 0.0);
  EXPECT_DOUBLE_EQ(v1[1], 0.0);

  // Test with constructor which takes three doubles as argument.
  Vector<dim> v2{1.0, 2.0};
  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);

  // Test with constructor which takes a std::array as argument.
  std::array<double, dim> arr{1.0, 2.0};
  Vector<dim> v3{arr};
  EXPECT_DOUBLE_EQ(v3[0], 1.0);
  EXPECT_DOUBLE_EQ(v3[1], 2.0);
}

/**
 * Test correctness of copy assignment operator of class Vector.
 */
TEST(Vector_2D, copy_assignment) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Copy Vector v1
  Vector<dim> v1{1.0, 2.0};
  Vector<dim> v2 = v1;

  // Change value of v1 and test if v2 is unchanged
  v1[0] = 5.0;
  EXPECT_DOUBLE_EQ(v2[0], 1.0);
}

/**
 * Test correctness of `operator*` of class Vector.
 */
TEST(Vector_2D, operatorMultiplicationOne) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0};
  Vector<dim> v2{1.0, 2.0};


  // Scalar product
  double scalarProduct = v1 * v2;

  // Check if v1 and v2 are unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);

  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);

  // Test values of v2
  EXPECT_DOUBLE_EQ(scalarProduct, 5);
}

/**
 * Test correctness of `operator+` of class Vector.
 */
TEST(Vector_2D, operatorAddition) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0};
  Vector<dim> v2{1.0, 2.0};

  Vector<dim> result = v1 + v2;

  // Check if v1 and v2 are unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);

  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 2.0);
  EXPECT_DOUBLE_EQ(result[1], 4.0);
}

/**
 * Test correctness of `operator-` of class Vector.
 */
TEST(Vector_2D, operatorSubtraction) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0};
  Vector<dim> v2{1.0, 2.0};

  Vector<dim> result = v1 - v2;

  // Check if v1 and v2 are unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);

  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 0.0);
  EXPECT_DOUBLE_EQ(result[1], 0.0);
}

/**
 * Test correctness of `operator*` of class Vector.
 */
TEST(Vector_2D, operatorMultiplicationTwo) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0};
  double factor = 2.0;

  Vector<dim> result = v1 * factor;

  // Check if v1 is unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 2.0);
  EXPECT_DOUBLE_EQ(result[1], 4.0);

  result = factor * v1;

  // Check if v1 is unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 2.0);
  EXPECT_DOUBLE_EQ(result[1], 4.0);
}

/**
 * Test correctness of `operator/` of class Vector.
 */
TEST(Vector_2D, operatorDivision) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Create test Vectors
  Vector<dim> v1{1.0, 2.0};
  double factor = 2.0;

  Vector<dim> result = v1 / factor;

  // Check if v1 is unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 0.5);
  EXPECT_DOUBLE_EQ(result[1], 1.0);
}
