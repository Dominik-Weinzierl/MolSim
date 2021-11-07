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
  Vector v1{};
  EXPECT_EQ(v1[0], 0.0);
  EXPECT_EQ(v1[1], 0.0);
  EXPECT_EQ(v1[2], 0.0);

  // Test with constructor which takes three doubles as argument
  Vector v2{1.0, 2.0, 3.0};
  EXPECT_EQ(v2[0], 1.0);
  EXPECT_EQ(v2[1], 2.0);
  EXPECT_EQ(v2[2], 3.0);

  // Test with constructor which takes a std::array as argument
  std::array<double, 3> arr{1.0, 2.0, 3.0};
  Vector v3{arr};
  EXPECT_EQ(v3[0], 1.0);
  EXPECT_EQ(v3[1], 2.0);
  EXPECT_EQ(v3[2], 3.0);
}

/**
 * Test correctness of copy assignment operator of class Vector.
 */
TEST(Vector, copy_assignment) { // NOLINT(cert-err58-cpp)
  // Copy Vector v1
  Vector v1{1.0, 2.0, 3.0};
  Vector v2 = v1;

  // Change value of v1 and test if v2 is unchanged
  v1[0] = 5.0;
  EXPECT_EQ(v2[0], 1.0);
}

/**
 * Test correctness of `operator+=` of class Vector.
 */
TEST(Vector, operatorAdditionAndAssignment) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector v1{1.0, 2.0, 3.0};
  Vector v2{1.0, 2.0, 3.0};

  // Add v1 to v2 and assign to v2
  v2 += v1;

  // Test values of v2
  EXPECT_EQ(v2[0], 2.0);
  EXPECT_EQ(v2[1], 4.0);
  EXPECT_EQ(v2[2], 6.0);

  // Check if v1 is unchanged
  EXPECT_EQ(v1[0], 1.0);
  EXPECT_EQ(v1[1], 2.0);
  EXPECT_EQ(v1[2], 3.0);
}

/**
 * Test correctness of `operator-=` of class Vector.
 */
TEST(Vector, operatorSubtractionAndAssignment) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector v1{1.0, 2.0, 3.0};
  Vector v2{1.0, 2.0, 3.0};

  // Sub v1 from v2 and assign to v2
  v2 -= v1;

  // Test values of v2
  EXPECT_EQ(v2[0], 0.0);
  EXPECT_EQ(v2[1], 0.0);
  EXPECT_EQ(v2[2], 0.0);

  // Check if v1 is unchanged
  EXPECT_EQ(v1[0], 1.0);
  EXPECT_EQ(v1[1], 2.0);
  EXPECT_EQ(v1[2], 3.0);
}

/**
 * Test correctness of `operator-` of class Vector.
 */
TEST(Vector, operatorUnary) { // NOLINT(cert-err58-cpp)
  // Create test Vector
  Vector v1{1.0, 2.0, 3.0};

  // Invert v1
  -v1;

  // Check values of v1
  EXPECT_EQ(v1[0], -1.0);
  EXPECT_EQ(v1[1], -2.0);
  EXPECT_EQ(v1[2], -3.0);
}

/**
 * Test correctness of `operator*=` with double of class Vector.
 */
TEST(Vector, operatorMultiplicationAndAssignmentWithDouble) { // NOLINT(cert-err58-cpp)
  // Create test Vector
  Vector v1{1.0, 2.0, 3.0};
  double factor = 2.0;

  // Scale Vector v1
  v1 *= factor;

  // Check values of v1
  EXPECT_EQ(v1[0], 2.0);
  EXPECT_EQ(v1[1], 4.0);
  EXPECT_EQ(v1[2], 6.0);
}

/**
 * Test correctness of `operator/=` with double of class Vector.
 */
TEST(Vector, operatorDivisionAndAssignmentWithDouble) { // NOLINT(cert-err58-cpp)
  // Create test Vector
  Vector v1{1.0, 2.0, 3.0};
  double factor = 2.0;

  // Scale Vector v1
  v1 /= factor;

  // Check values of v1
  EXPECT_EQ(v1[0], 0.5);
  EXPECT_EQ(v1[1], 1.0);
  EXPECT_EQ(v1[2], 1.5);
}

/**
 * Test correctness of `operator*` of class Vector.
 */
TEST(Vector, operatorMultiplication) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector v1{1.0, 2.0, 3.0};
  Vector v2{1.0, 2.0, 3.0};


  // Scalar product
  double scalarProduct = v1 * v2;

  // Check if v1 and v2 are unchanged
  EXPECT_EQ(v1[0], 1.0);
  EXPECT_EQ(v1[1], 2.0);
  EXPECT_EQ(v1[2], 3.0);

  EXPECT_EQ(v2[0], 1.0);
  EXPECT_EQ(v2[1], 2.0);
  EXPECT_EQ(v2[2], 3.0);

  // Test values of v2
  EXPECT_DOUBLE_EQ(scalarProduct, 14);
}