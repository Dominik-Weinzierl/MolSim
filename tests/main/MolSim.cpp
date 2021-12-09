#include <gtest/gtest.h>

#include "main/MolSim.h"

/**
 * ***************************************************
 * Test correct functionality of class MolSim.
 * ******************************************+********
 */

/**
 * Test correct setup of task 4 of work sheet 3.
 */
TEST(Main, setup_ws_03_water_drop_2D) { // NOLINT(cert-err58-cpp)
  MolSim<2> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../input/ws_03/water_drop.xml", "-b", "-2"}), 1);
  auto &cellContainer = dynamic_cast<LinkedCellContainer<2> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 709);
  EXPECT_EQ(cellContainer.getBoundaryCells().size(), 110);
  EXPECT_EQ(cellContainer.getHalosCells().size(), 118);
  EXPECT_EQ(cellContainer.getInnerCells().size(), 570);
  EXPECT_EQ(cellContainer.getCells().size(), 798);
}

/**
 * Test correct setup of task 4 of work sheet 3.
 */
TEST(Main, setup_ws_03_water_drop_3D) { // NOLINT(cert-err58-cpp)
  MolSim<3> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../input/ws_03/water_drop.xml", "-b", "-3"}), 1);
  auto &cellContainer = dynamic_cast<LinkedCellContainer<3> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 14147);
  EXPECT_EQ(cellContainer.getBoundaryCells().size(), 3010);
  EXPECT_EQ(cellContainer.getHalosCells().size(), 3602);
  EXPECT_EQ(cellContainer.getInnerCells().size(), 8550);
  EXPECT_EQ(cellContainer.getCells().size(), 15162);
}

/**
 * Test correct setup of task 2 of work sheet 3.
 */
TEST(Main, setup_ws_03_task_2) { // NOLINT(cert-err58-cpp)
  MolSim<2> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../input/ws_03/task_2_linked.xml", "-b", "-2"}), 1);
  auto &cellContainer = dynamic_cast<LinkedCellContainer<2> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 2400);
  EXPECT_EQ(cellContainer.getBoundaryCells().size(), 176);
  EXPECT_EQ(cellContainer.getHalosCells().size(), 184);
  EXPECT_EQ(cellContainer.getInnerCells().size(), 1624);
  EXPECT_EQ(cellContainer.getCells().size(), 1984);
}

/**
 * Test correct setup of task 2 of work sheet 3.
 */
TEST(Main, setup_ws_03_task_2_3D) { // NOLINT(cert-err58-cpp)
  MolSim<3> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../input/ws_03/task_2_linked.xml", "-b", "-3"}), 1);
  auto &cellContainer = dynamic_cast<LinkedCellContainer<3> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 2400);
  EXPECT_EQ(cellContainer.getBoundaryCells().size(), 3776);
  EXPECT_EQ(cellContainer.getHalosCells().size(), 4520);
  EXPECT_EQ(cellContainer.getInnerCells().size(), 1624);
  EXPECT_EQ(cellContainer.getCells().size(), 9920);
}

/**
 * Test correct setup for loading additional files.
 */
TEST(Main, setup_loading_additional_files) { // NOLINT(cert-err58-cpp)
  MolSim<2> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../tests/main/input/input_4.xml", "-b", "-2"}), 1);
  auto &cellContainer = dynamic_cast<DirectSumContainer<2> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 10);
}

/**
 * Test correct setup for loading additional files.
 */
TEST(Main, setup_loading_additional_files_3D) { // NOLINT(cert-err58-cpp)
  MolSim<3> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../tests/main/input/input_4.xml", "-b", "-3"}), 1);
  auto &cellContainer = dynamic_cast<DirectSumContainer<3> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 10);
}

/**
 * Test correct setup for loading additional files and shapes.
 */
TEST(Main, setup_loading_additional_files_and_shapes) { // NOLINT(cert-err58-cpp)
  MolSim<2> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../tests/main/input/input_5.xml", "-b", "-2"}), 1);
  auto &cellContainer = dynamic_cast<DirectSumContainer<2> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 2410);
}

/**
 * Test correct setup for loading additional files and shapes.
 */
TEST(Main, setup_loading_additional_files_and_shapes_3D) { // NOLINT(cert-err58-cpp)
  MolSim<3> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../tests/main/input/input_5.xml", "-b", "-3"}), 1);
  auto &cellContainer = dynamic_cast<DirectSumContainer<3> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 2410);
}
