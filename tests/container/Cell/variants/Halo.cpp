#include <gtest/gtest.h>

#include "container/LinkedCell/LinkedCellContainer.h"
#include "physics/LinkedCell/LinkedCell.h"


/**
 * ***************************************************
 * Test correct functionality of Halo cells
 * ******************************************+********
 */

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