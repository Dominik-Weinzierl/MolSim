#include <gtest/gtest.h>
#include "container/LinkedCell/LinkedCellContainer.h"
#include "particles/Particle.h"
#include "physics/LinkedCell.h"

/**
 * Tests the 2d setup of the LinkedCellContainer, the amount of cells that get generated and the
 * function getIndexBasedOnCoordinates
 */
TEST(LinkedCellContainer_2D, checkMeshProperties) {
  LinkedCellContainer<2> l{{Outflow, Outflow, Outflow, Outflow}, {1,1}, {3,3}, 1.5};
  l.init();

  //Test size
  auto size = static_cast<int>(l.getBoundaryAndInnerCells().size());
  EXPECT_EQ(size, 9);
  //Test getIndexBasedOnCoordinates
  auto i = 0;

  for(auto x = -1; x < l.getDomain()[0] + 1; x++){
    for(auto y = -1; y < l.getDomain()[1] + 1; y++){
      EXPECT_EQ(i, l.getIndexBasedOnCoordinates(
          Vector<2>{static_cast<double>(x), static_cast<double>(y)}));
        i++;
      }
    }
}

/**
 * Tests the 3d setup of the LinkedCellContainer, the amount of cells that get generated and the
 * function getIndexBasedOnCoordinates
 */
TEST(LinkedCellContainer_3D, checkMeshProperties) {
  LinkedCellContainer<3> l{{Outflow, Outflow, Outflow, Outflow, Outflow, Outflow}, {1,1, 1}, {3,3, 3}, 1.5};
  l.init();

  //Test size
  auto size = static_cast<int>(l.getBoundaryAndInnerCells().size());
  EXPECT_EQ(size, 27);
  //Test getIndexBasedOnCoordinates
  auto i = 0;

  for(auto z = -1; z < l.getDomain()[2] + 1; z++){
    for(auto x = -1; x < l.getDomain()[0] + 1; x++){
      for(auto y = -1; y < l.getDomain()[1] + 1; y++){
        EXPECT_EQ(i, l.getIndexBasedOnCoordinates(
            Vector<3>{static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)}));
        i++;
      }
    }
  }
}

/**
 * Checks the reflection of a Particle that moves too close to the border
 */
TEST(Boundary_2D, checkReflection) {
  LinkedCell<LennardJones, 2> linkedCell{};
  LinkedCellContainer<2> l{{Reflecting, Reflecting, Reflecting, Reflecting}, {2, 1}, {180, 90}, 3.0};
  l.init();
  ASSERT_TRUE(l.size() == 0);
  l.addParticle({{20, 20}, {0.0, -10.0}, 1.0});
  std::cout << l.getParticles()[0].getX() << std::endl;
  linkedCell.calculateNextStep(l, 0.0005);
  ASSERT_TRUE(l.size() == 1);
  for (auto i = 0; i < 10000; i++) {
    std::cout << l.getParticles()[0].getX() << std::endl;
    linkedCell.calculateNextStep(l, 0.0005);
  }
}

/**
 * Checks the removal of a Particle that moves out of the domain
 */
TEST(Halo_2D, checkOutflow) {
  LinkedCell<LennardJones, 2> linkedCell{};
  LinkedCellContainer<2> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1}, {3, 3}, 1.0};
  l.init();
  ASSERT_TRUE(l.size() == 0);
  l.addParticle({{0.1, 0.1}, {-1.0, 0.0}, 1.0});
  linkedCell.calculateNextStep(l, 1.225);
  ASSERT_TRUE(l.size() == 0);
}