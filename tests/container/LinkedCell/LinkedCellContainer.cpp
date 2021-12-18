#include <gtest/gtest.h>

#include "container/LinkedCell/LinkedCellContainer.h"
#include "physics/LinkedCell.h"

/**
 * ***************************************************
 * Test correct functionality of the linked cell container(s)
 * ******************************************+********
 */

/**
 * Tests the 2d setup of the LinkedCellContainer, the amount of cells that get generated and the
 * function getIndexBasedOnCoordinates, 2D
 */
TEST(LinkedCellContainer_2D, checkMeshProperties) {
  LinkedCellContainer<2> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1}, {3, 3}, 1.5};
  l.init();

  //Test size
  auto size = static_cast<int>(l.getBoundaryAndInnerCells().size());
  EXPECT_EQ(size, 9);

  //Test getIndexBasedOnCoordinates
  auto i = 0;

  for (auto x = -1; x < l.getDomain()[0] + 1; x++) {
    for (auto y = -1; y < l.getDomain()[1] + 1; y++) {
      EXPECT_EQ(i, l.getIndexBasedOnCoordinates(Vector<2>{static_cast<double>(x), static_cast<double>(y)}));
      EXPECT_EQ(l.getCells()[static_cast<unsigned long>(i)]->getPosition(), (Vector<2>{static_cast<double>(x), static_cast<double>(y)}));
      i++;
    }
  }
}

/**
 * Small version: Tests the 3d setup of the LinkedCellContainer, the amount of cells that get generated and the
 * function getIndexBasedOnCoordinates, 3D
 */
TEST(SmallLinkedCellContainer_3D, checkMeshProperties) {
  LinkedCellContainer<3> l{{Outflow, Outflow, Outflow, Outflow, Outflow, Outflow}, {1, 1, 1}, {3, 3, 3}, 1.5};
  l.init();

  //Test size
  auto size = static_cast<int>(l.getBoundaryAndInnerCells().size());
  EXPECT_EQ(size, 27);

  //Test getIndexBasedOnCoordinates
  auto i = 0;

  for (auto z = -1; z < l.getDomain()[2] + 1; z++) {
    for (auto x = -1; x < l.getDomain()[0] + 1; x++) {
      for (auto y = -1; y < l.getDomain()[1] + 1; y++) {
        EXPECT_EQ(i, l.getIndexBasedOnCoordinates(
            Vector<3>{static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)}));
        EXPECT_EQ(l.getCells()[static_cast<unsigned long>(i)]->getPosition(), (Vector<3>{static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)}));
        i++;
      }
    }
  }
}

/**
 * Huge version: Tests the 3d setup of the LinkedCellContainer, the amount of cells that get generated and the
 * function getIndexBasedOnCoordinates, 3D
 */
TEST(HugeLinkedCellContainer_3D, checkMeshProperties) {
  LinkedCellContainer<3> l{{Outflow, Outflow, Outflow, Outflow, Outflow, Outflow}, {2, 1, 3}, {24, 24, 27}, 3.5};
  l.init();

  //Test size
  auto size = static_cast<int>(l.getBoundaryAndInnerCells().size());
  EXPECT_EQ(size, 2592);

  //Test getIndexBasedOnCoordinates
  auto i = 0;

  for (auto z = -3; z < l.getDomain()[2] + 1; z += 3) {
    for (auto x = -2; x < l.getDomain()[0] + 1; x += 2) {
      for (auto y = -1; y < l.getDomain()[1] + 1; y += 1) {
        EXPECT_EQ(i, l.getIndexBasedOnCoordinates(
            Vector<3>{static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)}));
        EXPECT_EQ(l.getCells()[static_cast<unsigned long>(i)]->getPosition(), (Vector<3>{static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)}));
        i++;
      }
    }
  }
}

/**
 * Checks the reflection of a Particle that moves too close to the border, 2D
 */
TEST(Boundary_2D, checkReflection) {
  LinkedCell<LennardJones, 2> linkedCell{};
  LinkedCellContainer<2> l{{Reflecting, Reflecting, Reflecting, Reflecting}, {3, 3}, {9, 9}, 3.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{1.0, 1.0}, {-10.0, 0}, 1.0});

  l.init();

  double force = 0;

  for (int i = 0; i < 1000; ++i) {
    linkedCell.calculateNextStep(l, 0.0005, force);
    ASSERT_TRUE(l.size() == 1);
    auto &pos = l.getParticles()[0].getX();
    ASSERT_TRUE(pos[0] >= 0 && pos[0] < l.getDomain()[0]);
    ASSERT_TRUE(pos[1] >= 0 && pos[1] < l.getDomain()[1]);
  }
}

/**
 * Checks the reflection of a Particle that moves too close to the border, 3D
 */
TEST(Boundary_3D, checkReflection) {
  LinkedCell<LennardJones, 3> linkedCell{};
  LinkedCellContainer<3>
      l{{Reflecting, Reflecting, Reflecting, Reflecting, Reflecting, Reflecting}, {3, 3, 3}, {9, 9, 9}, 3.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{1.0, 1.0, 1.0}, {-10.0, -10.0, -10.0}, 1.0});

  l.init();

  double force = 0;

  for (int i = 0; i < 1000; ++i) {
    linkedCell.calculateNextStep(l, 0.0005, force);
    ASSERT_TRUE(l.size() == 1);
    auto &pos = l.getParticles()[0].getX();
    ASSERT_TRUE(pos[0] >= 0 && pos[0] < l.getDomain()[0]);
    ASSERT_TRUE(pos[1] >= 0 && pos[1] < l.getDomain()[1]);
    ASSERT_TRUE(pos[2] >= 0 && pos[2] < l.getDomain()[2]);
  }
}

/**
 * Checks the removal of a Particle that moves out of the domain, 2D
 */
TEST(Halo_2D, checkOutflow) {
  LinkedCell<LennardJones, 2> linkedCell{};
  LinkedCellContainer<2> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1}, {3, 3}, 1.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{0.1, 0.1}, {-1.0, -1.0}, 1.0});

  l.init();

  double force = 0;

  linkedCell.calculateNextStep(l, 0.5, force);
  ASSERT_TRUE(l.size() == 0);
}

/**
 * Checks the removal of a Particle that moves out of the domain, 2D
 */
TEST(Halo_3D, checkOutflow) {
  LinkedCell<LennardJones, 3> linkedCell{};
  LinkedCellContainer<3> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1, 1}, {3, 3, 3}, 1.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{0.1, 0.1, 0.1}, {-1.0, -1.0, -1.0}, 1.0});

  l.init();

  double force = 0;

  linkedCell.calculateNextStep(l, 0.5, force);
  ASSERT_TRUE(l.size() == 0);
}

/**
* Checks behavior when the CutOffRadius is greater than the cell size, 2D
*/
TEST(LinkedCellContainer_2D, checkCutoffRadiusGreaterThanCellSize) {
  LinkedCell<LennardJones, 2> linkedCell{};
  LinkedCellContainer<2> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1}, {3, 3}, 2};

  l.addParticle({{0.1, 0.1}, {-1.0, 0.0}, 1.0});
  l.addParticle({{1.5, 1.5}, {-1.0, 0.0}, 1.0});

  l.init();

  auto force = l.getParticles()[1].getF();

  double additionalGravitation = 0;
  linkedCell.calculateNextStep(l, 0.0005, additionalGravitation);

  ASSERT_TRUE(force != l.getParticles()[1].getF());
}

/**
* Checks behavior when the CutOffRadius is greater than the cell size, 3D
*/
TEST(LinkedCellContainer_3D, checkCutoffRadiusGreaterThanCellSize) {
  LinkedCell<LennardJones, 3> linkedCell{};
  LinkedCellContainer<3> l{{Outflow, Outflow, Outflow, Outflow, Outflow, Outflow}, {1, 1, 1}, {3, 3, 3}, 2};

  l.addParticle({{0.1, 0.1, 0.1}, {-1.0, 0.0, 0.0}, 1.0});
  l.addParticle({{1.5, 1.5, 1.5}, {-1.0, 0.0, 0.0}, 1.0});

  l.init();

  auto force = l.getParticles()[1].getF();
  double additionalGravitation = 0;
  linkedCell.calculateNextStep(l, 0.0005, additionalGravitation);

  ASSERT_TRUE(force == l.getParticles()[1].getF());
}

/**
* Checks behavior when the CutOffRadius is smaller than the cell size, 2D
*/
TEST(LinkedCellContainer_2D, checkCutoffRadiusLessThanCellSize) {
  LinkedCell<LennardJones,2> linkedCell{};
  LinkedCellContainer<2> l{{Outflow, Outflow, Outflow, Outflow}, {3, 3}, {9,9}, 2};

  l.addParticle({{2.9, 2.9}, {-1.0, 0.0}, 1.0});
  l.addParticle({{3.1, 3.1}, {-1.0, 0.0}, 1.0});

  l.init();

  auto force = l.getParticles()[1].getF();

  double additionalGravitation = 0;
  linkedCell.calculateNextStep(l, 0.0005, additionalGravitation);

  ASSERT_TRUE(force != l.getParticles()[1].getF());
}

/**
* Checks linking behavior if cutoff radius is greater than cell size and has (no) common divisor.
*/
TEST(LinkedCellContainer_2D, checkCutoffRadiusWithRest) {
  LinkedCellContainer<2> l_1{{Outflow, Outflow, Outflow, Outflow}, {2, 2}, {6, 6}, 3};
  l_1.init();

  Boundary<2> &l_1_cell = l_1.getBoundaryCells()[0];
  EXPECT_EQ(l_1_cell.getNeighbours().size(), 8);

  LinkedCellContainer<2> l_2{{Outflow, Outflow, Outflow, Outflow}, {2, 2}, {6, 6}, 2};
  l_2.init();

  Boundary<2> &l_2_cell = l_2.getBoundaryCells()[0];
  EXPECT_EQ(l_2_cell.getNeighbours().size(), 3);
}

/**
* Checks behavior if Particle gets out of bound.
*/
TEST(LinkedCellContainer, checkParticleGetsOutOfBounds) {
  LinkedCellContainer<2> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1}, {3, 36}, 3};

  l.addParticle({{-5, 0}, {-1.0, 0.0}, 1.0});

  EXPECT_THROW(l.init(), std::invalid_argument);
}
