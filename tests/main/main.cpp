#include <gtest/gtest.h>

#include "main/MolSim.h"

/**
 * ***************************************************
 * Test correct functionality of larger simulations.
 * ******************************************+********
 */

/**
 * Test which perform complex simulations which test the complete structure.
 * In this case we expect no issues with reflecting boundaries and the linked cell algorithm in 2D.
 */
TEST(Main, boundary_linked_cell_2D) { // NOLINT(cert-err58-cpp)
  EXPECT_EQ(MolSim<2>::run({"-x", "-f", "../../tests/main/input/input_1.xml", "-b", "-2"}), 0);
}

/**
 * Test which perform complex simulations which test the complete structure.
 * In this case we expect no issues with reflecting boundaries and the linked cell algorithm in 3D.
 */
TEST(Main, boundary_linked_cell_3D) { // NOLINT(cert-err58-cpp)
  EXPECT_EQ(MolSim<3>::run({"-x", "-f", "../../tests/main/input/input_1.xml", "-b", "-3"}), 0);
}

/**
 * Test which perform complex simulations which test the complete structure.
 * In this case we expect no issues with outflow boundaries and the linked cell algorithm in 2D.
 */
TEST(Main, outflow_linked_cell_2D) { // NOLINT(cert-err58-cpp)
  EXPECT_EQ(MolSim<2>::run({"-x", "-f", "../../tests/main/input/input_2.xml", "-b", "-2"}), 0);
}

/**
 * Test which perform complex simulations which test the complete structure.
 * In this case we expect no issues with outflow boundaries and the linked cell algorithm in 3D.
 */
TEST(Main, outflow_linked_cell_3D) { // NOLINT(cert-err58-cpp)
  EXPECT_EQ(MolSim<3>::run({"-x", "-f", "../../tests/main/input/input_2.xml", "-b", "-3"}), 0);

}

/**
 * In this test we test invalid input and to get an exception.
 */
TEST(Main, invalid_input_2D) { // NOLINT(cert-err58-cpp)
  EXPECT_THROW(MolSim<2>::run({"-x", "-f", "../../tests/main/input/input_3.xml", "-b", "-2"}), std::invalid_argument);
}

/**
 * In this test we test invalid input and expect to get an exception.
 */
TEST(Main, invalid_input_3D) { // NOLINT(cert-err58-cpp)
  EXPECT_THROW(MolSim<3>::run({"-x", "-f", "../../tests/main/input/input_3.xml", "-b", "-3"}), std::invalid_argument);
}



