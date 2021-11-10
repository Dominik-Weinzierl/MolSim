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
  EXPECT_DOUBLE_EQ(v1[0], 0.0);
  EXPECT_DOUBLE_EQ(v1[1], 0.0);
  EXPECT_DOUBLE_EQ(v1[2], 0.0);

  // Test with constructor which takes three doubles as argument
  Vector v2{1.0, 2.0, 3.0};
  EXPECT_DOUBLE_EQ(v2[0], 1.0);
  EXPECT_DOUBLE_EQ(v2[1], 2.0);
  EXPECT_DOUBLE_EQ(v2[2], 3.0);

  // Test with constructor which takes a std::array as argument
  std::array<double, 3> arr{1.0, 2.0, 3.0};
  Vector v3{arr};
  EXPECT_DOUBLE_EQ(v3[0], 1.0);
  EXPECT_DOUBLE_EQ(v3[1], 2.0);
  EXPECT_DOUBLE_EQ(v3[2], 3.0);
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
  EXPECT_DOUBLE_EQ(v2[0], 1.0);
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
  EXPECT_DOUBLE_EQ(v2[0], 2.0);
  EXPECT_DOUBLE_EQ(v2[1], 4.0);
  EXPECT_DOUBLE_EQ(v2[2], 6.0);

  // Check if v1 is unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);
  EXPECT_DOUBLE_EQ(v1[2], 3.0);
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
  EXPECT_DOUBLE_EQ(v2[0], 0.0);
  EXPECT_DOUBLE_EQ(v2[1], 0.0);
  EXPECT_DOUBLE_EQ(v2[2], 0.0);

  // Check if v1 is unchanged
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
  EXPECT_DOUBLE_EQ(v1[1], 2.0);
  EXPECT_DOUBLE_EQ(v1[2], 3.0);
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
  EXPECT_DOUBLE_EQ(v1[0], -1.0);
  EXPECT_DOUBLE_EQ(v1[1], -2.0);
  EXPECT_DOUBLE_EQ(v1[2], -3.0);
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
  EXPECT_DOUBLE_EQ(v1[0], 2.0);
  EXPECT_DOUBLE_EQ(v1[1], 4.0);
  EXPECT_DOUBLE_EQ(v1[2], 6.0);
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
  EXPECT_DOUBLE_EQ(v1[0], 0.5);
  EXPECT_DOUBLE_EQ(v1[1], 1.0);
  EXPECT_DOUBLE_EQ(v1[2], 1.5);
}

/**
 * Test correctness of `operator*` of class Vector.
 */
TEST(Vector, operatorMultiplicationOne) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector v1{1.0, 2.0, 3.0};
  Vector v2{1.0, 2.0, 3.0};


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
 * Test correctness of `operator[]` of class Vector.
 */
TEST(Vector, operatorIndexBasedAccessWithReferenceAsReturn) { // NOLINT(cert-err58-cpp)
  // Create test Vector
  Vector v1{1.0, 2.0, 3.0};

  auto &first = v1[0];

  // Check value of first
  EXPECT_DOUBLE_EQ(first, 1.0);

  // Change value of first
  first += 5.0;

  // Check value of v1
  EXPECT_DOUBLE_EQ(v1[0], 6.0);
}

/**
 * Test correctness of `operator[]` of class Vector.
 */
TEST(Vector, operatorIndexBasedAccessWithValueAsReturn) { // NOLINT(cert-err58-cpp)
  // Create test Vector
  Vector v1{1.0, 2.0, 3.0};

  auto first = v1[0];

  // Check value of first
  EXPECT_DOUBLE_EQ(first, 1.0);

  // Change value of first
  first += 5.0;

  // Check value of v1
  EXPECT_DOUBLE_EQ(v1[0], 1.0);
}

/**
 * Test correctness of `operator==` of class Vector.
 */
TEST(Vector, operatorEqual) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector v1{1.0, 2.0, 3.0};
  Vector v2{1.0, 2.0, 3.0};

  // Check equal
  EXPECT_TRUE(v1 == v2);

  v2 *= 2.0;

  // Check not equal
  EXPECT_FALSE(v1 == v2);
}

/**
 * Test correctness of `operator+` of class Vector.
 */
TEST(Vector, operatorAddition) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector v1{1.0, 2.0, 3.0};
  Vector v2{1.0, 2.0, 3.0};

  Vector result = v1 + v2;

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
  Vector v1{1.0, 2.0, 3.0};
  Vector v2{1.0, 2.0, 3.0};

  Vector result = v1 - v2;

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
  Vector v1{1.0, 2.0, 3.0};
  double factor = 2.0;

  Vector result = v1 * factor;

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
  Vector v1{1.0, 2.0, 3.0};
  double factor = 2.0;

  Vector result = v1 / factor;

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
 * Test correctness of function get() of class Vector.
 */
TEST(Vector, get) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector v1{1.0, 2.0, 3.0};

  const std::array<double, 3> &get = v1.get();

  // Scale to check still the same
  v1 *= 2.0;

  // Check get == v1
  EXPECT_DOUBLE_EQ(v1[0], get[0]);
  EXPECT_DOUBLE_EQ(v1[1], get[1]);
  EXPECT_DOUBLE_EQ(v1[2], get[2]);
}

/**
 * Test correctness of function size() of class Vector. This should be always 3.
 */
TEST(Vector, size) { // NOLINT(cert-err58-cpp)
  // Create test Vectors
  Vector v1{1.0, 2.0, 3.0};

  // Expect size to be three
  EXPECT_EQ(v1.size(), 3);
}
