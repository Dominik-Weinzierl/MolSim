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
 * Test correct setup of task 2 of work sheet 4.
 */
TEST(Main, setup_ws_04_task_2_small) { // NOLINT(cert-err58-cpp)
  MolSim<2> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../input/ws_04/task_2_small_cell_size_1.xml", "-b", "-2"}), 1);
  auto &cellContainer = dynamic_cast<LinkedCellContainer<2> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 1400);
  EXPECT_EQ(cellContainer.getBoundaryCells().size(), 194);
  EXPECT_EQ(cellContainer.getHalosCells().size(), 202);
  EXPECT_EQ(cellContainer.getInnerCells().size(), 2074);
  EXPECT_EQ(cellContainer.getCells().size(), 2470);
}

/**
 * Test correct setup of task 2 of work sheet 4.
 */
TEST(Main, setup_ws_04_task_2_small_3D) { // NOLINT(cert-err58-cpp)
  MolSim<3> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../input/ws_04/task_2_small_cell_size_1.xml", "-b", "-3"}), 1);
  auto &cellContainer = dynamic_cast<LinkedCellContainer<3> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 70000);
  EXPECT_EQ(cellContainer.getBoundaryCells().size(), 16370);
  EXPECT_EQ(cellContainer.getHalosCells().size(), 17666);
  EXPECT_EQ(cellContainer.getInnerCells().size(), 126514);
  EXPECT_EQ(cellContainer.getCells().size(), 160550);
}

/**
 * Test correct setup of task 2 of work sheet 4.
 */
TEST(Main, setup_ws_04_task_2_big) { // NOLINT(cert-err58-cpp)
  MolSim<2> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../input/ws_04/task_2_big_cell_size_1.xml", "-b", "-2"}), 1);
  auto &cellContainer = dynamic_cast<LinkedCellContainer<2> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 10000);
  EXPECT_EQ(cellContainer.getBoundaryCells().size(), 704);
  EXPECT_EQ(cellContainer.getHalosCells().size(), 712);
  EXPECT_EQ(cellContainer.getInnerCells().size(), 15496);
  EXPECT_EQ(cellContainer.getCells().size(), 16912);
}

/**
 * Test correct setup of task 2 of work sheet 4.
 */
TEST(Main, setup_ws_04_task_2_big_3D) { // NOLINT(cert-err58-cpp)
  MolSim<3> sim{};
  EXPECT_EQ(sim.setup({"-x", "-f", "../../input/ws_04/task_2_big_cell_size_1.xml", "-b", "-3"}), 1);
  auto &cellContainer = dynamic_cast<LinkedCellContainer<3> &>(*(sim.getParticleContainer()));
  EXPECT_EQ(cellContainer.size(), 2500000);
  EXPECT_EQ(cellContainer.getBoundaryCells().size(), 242192);
  EXPECT_EQ(cellContainer.getHalosCells().size(), 247424);
  EXPECT_EQ(cellContainer.getInnerCells().size(), 4617808);
  EXPECT_EQ(cellContainer.getCells().size(), 5107424);
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
