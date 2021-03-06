#include <gtest/gtest.h>

#include "container/LinkedCell/LinkedCellContainer.h"
#include "physics/LinkedCell/LinkedCell.h"

/**
 * ***************************************************
 * Test correct functionality of the linked cell container(s).
 * ******************************************+********
 */

static auto eps = std::numeric_limits<double>::epsilon() * 100;


/**
 * Tests the 2d setup of the LinkedCellContainer, the amount of cells that get generated and the
 * function getIndexBasedOnCoordinates, 2D.
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
      EXPECT_EQ(l.getCells()[static_cast<unsigned long>(i)]->getPosition(),
                (Vector<2>{static_cast<double>(x), static_cast<double>(y)}));
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
        EXPECT_EQ(l.getCells()[static_cast<unsigned long>(i)]->getPosition(),
                  (Vector<3>{static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)}));
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
        EXPECT_EQ(l.getCells()[static_cast<unsigned long>(i)]->getPosition(),
                  (Vector<3>{static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)}));
        i++;
      }
    }
  }
}

/**
 * Test that Newton is used correctly, 2D.
 */
TEST(LinkedCellContainer_2D, checkNewton) {
  LinkedCellContainer<2> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1}, {3, 3}, 1.0};
  l.init();

  for (auto *cell: l.getBoundaryAndInnerCells()) {
    for (auto *n: cell->getNeighbours()) {
      for (auto *s: n->getNeighbours()) {
        ASSERT_TRUE(s != cell);
      }
    }
  }
}

/**
 * Test that Newton is used correctly, 3D.
 */
TEST(LinkedCellContainer_3D, checkNewton) {
  LinkedCellContainer<3> l{{Outflow, Outflow, Outflow, Outflow, Outflow, Outflow}, {1, 1, 1}, {3, 3, 3}, 1.0};
  l.init();

  for (auto *cell: l.getBoundaryAndInnerCells()) {
    for (auto *n: cell->getNeighbours()) {
      for (auto *s: n->getNeighbours()) {
        ASSERT_TRUE(s != cell);
      }
    }
  }
}

/**
 * Tests the linked cells which are used to calculate the force, 2D.
 */
TEST(LinkedCellContainer_2D, checkNewtonPeriodic) {
  LinkedCellContainer<2> l{{Periodic, Periodic, Periodic, Periodic}, {1, 1}, {3, 3}, 1.0};
  l.init();

  for (auto *cell: l.getCells()) {
    for (auto &t: cell->getPeriodicNeighbours()) {
      auto *neighbour = std::get<0>(t);
      for (auto &s: neighbour->getPeriodicNeighbours()) {
        ASSERT_TRUE(std::get<0>(s) != cell);
      }
    }
  }
}

/**
 * Tests the linked cells which are used to calculate the force, 3D.
 */
TEST(LinkedCellContainer_3D, checkNewtonPeriodic) {
  LinkedCellContainer<3> l{{Periodic, Periodic, Periodic, Periodic, Periodic, Periodic}, {1, 1, 1}, {3, 3, 3}, 1.0};
  l.init();

  for (auto *cell: l.getCells()) {
    for (auto &t: cell->getPeriodicNeighbours()) {
      auto *neighbour = std::get<0>(t);
      for (auto &s: neighbour->getPeriodicNeighbours()) {
        ASSERT_TRUE(std::get<0>(s) != cell);
      }
    }
  }
}

/**
* Checks behavior when the CutOffRadius is greater than the cell size, 2D.
*/
TEST(LinkedCellContainer_2D, checkCutoffRadiusGreaterThanCellSize) {
  const size_t dim = 2;
  LinkedCell<LennardJones, dim> linkedCell{};
  LinkedCellContainer<dim> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1}, {3, 3}, 2};

  l.addParticle({{0.1, 0.1}, {-1.0, 0.0}, 1.0});
  l.addParticle({{1.5, 1.5}, {-1.0, 0.0}, 1.0});
  l.init();

  auto force = l.getParticles()[1].getF();

  Vector<dim> additionalGravitation{0.0, 0.0};
  linkedCell.calculateNextStep(l, 0.0005, additionalGravitation, {});

  ASSERT_TRUE(force != l.getParticles()[1].getF());
}

/**
* Checks behavior when the CutOffRadius is greater than the cell size, 3D.
*/
TEST(LinkedCellContainer_3D, checkCutoffRadiusGreaterThanCellSize) {
  const size_t dim = 3;
  LinkedCell<LennardJones, dim> linkedCell{};
  LinkedCellContainer<dim> l{{Outflow, Outflow, Outflow, Outflow, Outflow, Outflow}, {1, 1, 1}, {3, 3, 3}, 2};

  l.addParticle({{0.1, 0.1, 0.1}, {-1.0, 0.0, 0.0}, 1.0});
  l.addParticle({{1.5, 1.5, 1.5}, {-1.0, 0.0, 0.0}, 1.0});
  l.init();

  auto force = l.getParticles()[1].getF();
  Vector<dim> additionalGravitation{0, 0, 0};
  linkedCell.calculateNextStep(l, 0.0005, additionalGravitation, {});

  ASSERT_TRUE(force == l.getParticles()[1].getF());
}

/**
* Checks behavior when the CutOffRadius is smaller than the cell size, 2D.
*/
TEST(LinkedCellContainer_2D, checkCutoffRadiusLessThanCellSize) {
  const size_t dim = 2;
  LinkedCell<LennardJones, dim> linkedCell{};
  LinkedCellContainer<dim> l{{Outflow, Outflow, Outflow, Outflow}, {3, 3}, {9, 9}, 2};

  l.addParticle({{2.9, 2.9}, {-1.0, 0.0}, 1.0});
  l.addParticle({{3.1, 3.1}, {-1.0, 0.0}, 1.0});
  l.init();

  auto force = l.getParticles()[1].getF();

  Vector<dim> additionalGravitation{0, 0};
  linkedCell.calculateNextStep(l, 0.0005, additionalGravitation, {});

  ASSERT_TRUE(force != l.getParticles()[1].getF());
}

/**
* Checks linking behavior if cutoff radius is greater than cell size and has (no) common divisor, 2D.
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
  LinkedCellContainer<2> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1}, {3, 3}, 3};

  l.addParticle({{-5, 0}, {-1.0, 0.0}, 1.0});

  EXPECT_THROW(l.init(), std::invalid_argument);
}

/**
* Checks mixing rule is applied correctly.
*/
TEST(LinkedCellContainer, mixingRule) {
  // Different zeroCrossing and potentialWellDepth
  Particle<2> p1{{1, 0}, {-1.0, 0.0}, 1.0, 1.0, 5.0, 1};
  Particle<2> p2{{2.5, 0}, {-1.0, 0.0}, 1.0, 2.0, 4.0, 2};

  double l2Norm = Physics<LennardJones, 2>::calcL2NormSquare(p1, p2);
  Vector<2> force_1 = LennardJones::calculateForceBetweenTwoParticles(p1, p2, l2Norm);

  // Same zeroCrossing and potentialWellDepth
  Particle<2> p3{{1, 0}, {-1.0, 0.0}, 1.0, 1.0, 5.0, 1};
  Particle<2> p4{{2.5, 0}, {-1.0, 0.0}, 1.0, 1.0, 5.0, 2};

  l2Norm = Physics<LennardJones, 2>::calcL2NormSquare(p3, p4);
  Vector<2> force_2 = LennardJones::calculateForceBetweenTwoParticles(p3, p4, l2Norm);

  EXPECT_NE(force_1, force_2);

  EXPECT_NEAR(force_1[0], -71.554175279993274, eps);
  EXPECT_NEAR(force_1[1], 0.0, eps);
}

