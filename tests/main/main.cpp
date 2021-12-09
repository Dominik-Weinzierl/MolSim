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

/**
 * Test help text.
 */
TEST(Main, help) { // NOLINT(cert-err58-cpp)
  testing::internal::CaptureStdout();
  ParserStrategy<2>::showUsage();
  auto help_text = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  EXPECT_EQ(MolSim<2>::run({"-h"}), 0);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output, help_text);

  testing::internal::CaptureStdout();
  EXPECT_EQ(MolSim<2>::run({"--help"}), 0);
  output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output, help_text);

  testing::internal::CaptureStdout();
  EXPECT_EQ(MolSim<2>::run({}), 0);
  output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output, help_text);
}

/**
 * In this test we test the simulation from worksheet 1.
 */
TEST(Main, ws_01_eingabe_sonne) { // NOLINT(cert-err58-cpp)
  EXPECT_EQ(MolSim<3>::run(
      {"--filename", "../../input/ws_01/eingabe-sonne.txt", "--t_end", "1000", "--delta_t", "0.014", "--physics",
       "gravitation", "--benchmark"}), 0);
}

/**
 * In this test we test the simulation from worksheet 1.
 */
TEST(Main, ws_01_sun_system) { // NOLINT(cert-err58-cpp)
  EXPECT_EQ(MolSim<3>::run(
      {"--filename", "../../input/ws_01/sun_system.txt", "--t_end", "1000", "--delta_t", "0.014", "--physics",
       "gravitation", "--benchmark"}), 0);
}

/**
 * In this test we test the simulation from worksheet 2.
 */
TEST(Main, ws_02_task_3) { // NOLINT(cert-err58-cpp)
  EXPECT_EQ(MolSim<3>::run({"-x", "-f", "../../input/ws_02/input_task_3.xml", "-b", "-2"}), 0);
}

/**
 * In this test we test the simulation from worksheet 3.
 */
TEST(Main, ws_03_task_2) { // NOLINT(cert-err58-cpp)
  EXPECT_EQ(MolSim<3>::run({"-x", "-f", "../../input/ws_03/task_2_linked.xml", "-b", "-2"}), 0);
}
