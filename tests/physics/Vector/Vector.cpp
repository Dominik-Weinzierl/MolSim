#include <gtest/gtest.h>
#include <physics/Vector/Vector.h>

/**
 * ************************************************
 * Test correct functionality of the class Vector
 * ******************************************+*****
 */


/**
 * Test correctness of constructors of class Vector.
 */
TEST(Vector, constructor) { // NOLINT(cert-err58-cpp)
  // Test with default constructor
  Vector<3> v1{};
  EXPECT_DOUBLE_EQ(v1[0], 0.0);
  EXPECT_DOUBLE_EQ(v1[1], 0.0);
  EXPECT_DOUBLE_EQ(v1[2], 0.0);

  // Test with constructor which takes three doubles as argument
  Vector<3> v2{1.0, 2.0, 3.0};
  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);
  EXPECT_DOUBLE_EQ(v2[2], 3.0);

  // Test with constructor which takes a std::array as argument
  std::array<double, 3> arr{1.0, 2.0, 3.0};
  Vector<3> v3{arr};
  EXPECT_DOUBLE_EQ(v3[0], 1.0);
  EXPECT_DOUBLE_EQ(v3[1], 2.0);
  EXPECT_DOUBLE_EQ(v3[2], 3.0);
}

/**
 * Test correctness of copy assignment operator of class Vector.
 */
TEST(Vector, copy_assignment) { // NOLINT(cert-err58-cpp)
  // Copy Vector v1
  Vector<3> v1{1.0, 2.0, 3.0};
  Vector<3> v2 = v1;

  // Change value of v1 and test if v2 is unchanged
  v1[0] = 5.0;
  EXPECT_DOUBLE_EQ(v2[0], 1.0);
}

/**
 * Test correctness of `operator*` of class Vector.
 */
TEST(Vector, operatorMultiplicationOne) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector<3> v1{1.0, 2.0, 3.0};
  Vector<3> v2{1.0, 2.0, 3.0};


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
TEST(Vector, operatorAddition) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector<3> v1{1.0, 2.0, 3.0};
  Vector<3> v2{1.0, 2.0, 3.0};

  Vector<3> result = v1 + v2;

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
TEST(Vector, operatorSubtraction) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector<3> v1{1.0, 2.0, 3.0};
  Vector<3> v2{1.0, 2.0, 3.0};

  Vector<3> result = v1 - v2;

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
TEST(Vector, operatorMultiplicationTwo) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector<3> v1{1.0, 2.0, 3.0};
  double factor = 2.0;

  Vector<3> result = v1 * factor;

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
TEST(Vector, operatorDivision) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector<3> v1{1.0, 2.0, 3.0};
  double factor = 2.0;

  Vector<3> result = v1 / factor;

  // Check if v1 is unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);
  EXPECT_DOUBLE_EQ(v1[2], 3.0);

  // Check value of result
  EXPECT_DOUBLE_EQ(result[0], 0.5);
  EXPECT_DOUBLE_EQ(result[1], 1.0);
  EXPECT_DOUBLE_EQ(result[2], 1.5);
}