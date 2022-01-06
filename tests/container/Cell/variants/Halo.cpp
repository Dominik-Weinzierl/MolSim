#include <gtest/gtest.h>

#include "container/LinkedCell/LinkedCellContainer.h"
#include "physics/LinkedCell.h"


/**
 * ***************************************************
 * Test correct functionality of Halo cells
 * ******************************************+********
 */

/**
 * Checks the removal of a Particle that moves out of the domain, 2D
 */
TEST(Halo_2D, checkOutflow) {
  const size_t dim = 2;
  LinkedCell<LennardJones, dim> linkedCell{};
  LinkedCellContainer<dim> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1}, {3, 3}, 1.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{0.1, 0.1}, {-1.0, -1.0}, 1.0});
  l.init();

  Vector<dim> force{0.0, 0.0};

  linkedCell.calculateNextStep(l, 0.5, force, {});
  ASSERT_TRUE(l.size() == 0);
}

/**
 * Checks the removal of a Particle that moves out of the domain, 2D
 */
TEST(Halo_3D, checkOutflow) {
  const size_t dim = 3;
  LinkedCell<LennardJones, dim> linkedCell{};
  LinkedCellContainer<dim> l{{Outflow, Outflow, Outflow, Outflow}, {1, 1, 1}, {3, 3, 3}, 1.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{0.1, 0.1, 0.1}, {-1.0, -1.0, -1.0}, 1.0});
  l.init();

  Vector<dim> force{0.0, 0.0, 0.0};

  linkedCell.calculateNextStep(l, 0.5, force, {});
  ASSERT_TRUE(l.size() == 0);
}