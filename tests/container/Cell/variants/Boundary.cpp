#include <gtest/gtest.h>

#include "container/LinkedCell/LinkedCellContainer.h"
#include "physics/LinkedCell.h"

/**
 * ***************************************************
 * Test correct functionality of Boundary cells
 * ******************************************+********
 */

static auto eps = std::numeric_limits<double>::epsilon() * 100;


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
 * Checks the periodic movement of Particles in 2D.
 */
TEST(Boundary_2D, checkPeriodic) {
  LinkedCell<LennardJones, 2> linkedCell{};
  LinkedCellContainer<2> l{{Periodic, Periodic, Periodic, Periodic}, {3, 3}, {9, 9}, 3.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{1.0, 1.0}, {-10.0, 0}, 1.0});

  l.init();

  double force = 0;

  for (int i = 0; i < 500; ++i) {
    linkedCell.calculateNextStep(l, 0.0005, force);
  }

  ASSERT_TRUE(l.getParticles()[0].getX()[0] > 1.0);
  ASSERT_TRUE(l.getParticles()[0].getX()[1] == 1.0);
}

/**
 * Checks the periodic movement of Particles in 3D.
 */
TEST(Boundary_3D, checkPeriodic) {
  LinkedCell<LennardJones, 3> linkedCell{};
  LinkedCellContainer<3> l{{Periodic, Periodic, Periodic, Periodic, Periodic, Periodic}, {3, 3, 3}, {9, 9, 9}, 3.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{1.0, 1.0, 1.0}, {0.0, 0.0, -10.0}, 1.0});

  l.init();

  double force = 0;

  for (int i = 0; i < 500; ++i) {
    linkedCell.calculateNextStep(l, 0.0005, force);
  }

  ASSERT_TRUE(l.getParticles()[0].getX()[2] > 1.0);
  ASSERT_TRUE(l.getParticles()[0].getX()[1] == 1.0);
  ASSERT_TRUE(l.getParticles()[0].getX()[0] == 1.0);
}

/**
 * Checks the periodic force.
 */
TEST(Boundary_2D, checkPeriodicForce) {
  LinkedCell<LennardJones, 2> linkedCell{};
  LinkedCellContainer<2> l{{Periodic, Periodic, Periodic, Periodic}, {3, 3}, {9, 9}, 3.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{1.0, 1.0}, {0.0, 0}, 1.0});
  l.addParticle({{8.0, 1.0}, {0.0, 0}, 1.0});

  l.init();

  double force = 0;

  linkedCell.calculateNextStep(l, 0.0005, force);

  ASSERT_NEAR(l.getParticles()[0].getF()[0], -l.getParticles()[1].getF()[0], eps);
  ASSERT_NEAR(l.getParticles()[0].getF()[1], -l.getParticles()[1].getF()[1], eps);
  ASSERT_TRUE(l.getParticles()[0].getF() != (Vector<2>{0, 0}));
}

/**
 * Checks the periodic force.
 */
TEST(Boundary_3D, checkPeriodicForce) {
  LinkedCell<LennardJones, 3> linkedCell{};
  LinkedCellContainer<3> l{{Periodic, Periodic, Periodic, Periodic, Periodic, Periodic}, {3, 3, 3}, {9, 9, 9}, 3.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{0.5, 0.5, 0.5}, {0.0, 0.0, 0.0}, 1.0});
  l.addParticle({{8.0, 8.0, 8.0}, {0.0, 0, 0.0}, 1.0});

  l.init();

  double force = 0;

  linkedCell.calculateNextStep(l, 0.0005, force);

  ASSERT_NEAR(l.getParticles()[0].getF()[0], -l.getParticles()[1].getF()[0], eps);
  ASSERT_NEAR(l.getParticles()[0].getF()[1], -l.getParticles()[1].getF()[1], eps);
  ASSERT_NEAR(l.getParticles()[0].getF()[2], -l.getParticles()[1].getF()[2], eps);
  ASSERT_TRUE(l.getParticles()[0].getF() != (Vector<3>{0, 0, 0}));
}

/**
 * Checks that the periodic force is only applied on the periodic sides.
 */
TEST(Boundary_2D, checkPeriodicForceNotAppliedOnSides) {
  LinkedCell<LennardJones, 2> linkedCell{};
  LinkedCellContainer<2> l{{Outflow, Outflow, Periodic, Periodic}, {3, 3}, {9, 9}, 3.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{0.5, 5.0}, {0.0, 0}, 1.0});
  l.addParticle({{8.5, 5.0}, {0.0, 0}, 1.0});

  l.init();

  double force = 0;

  linkedCell.calculateNextStep(l, 0.0005, force);

  ASSERT_NEAR(l.getParticles()[0].getF()[0], -l.getParticles()[1].getF()[0], eps);
  ASSERT_NEAR(l.getParticles()[0].getF()[1], -l.getParticles()[1].getF()[1], eps);
  ASSERT_TRUE(l.getParticles()[0].getF() == (Vector<2>{0, 0}));
}

/**
 * Checks that the periodic force is only applied on the periodic sides.
 */
TEST(Boundary_2D, checkPeriodicForceNotAppliedOnTopAndBottom) {
  LinkedCell<LennardJones, 2> linkedCell{};
  LinkedCellContainer<2> l{{Periodic, Periodic, Outflow, Outflow}, {3, 3}, {9, 9}, 3.0};
  ASSERT_TRUE(l.size() == 0);

  l.addParticle({{5.0, 0.5}, {0.0, 0}, 1.0});
  l.addParticle({{5.0, 8.5}, {0.0, 0}, 1.0});

  l.init();

  double force = 0;

  linkedCell.calculateNextStep(l, 0.0005, force);

  ASSERT_NEAR(l.getParticles()[0].getF()[0], -l.getParticles()[1].getF()[0], eps);
  ASSERT_NEAR(l.getParticles()[0].getF()[1], -l.getParticles()[1].getF()[1], eps);
  ASSERT_TRUE(l.getParticles()[0].getF() == (Vector<2>{0, 0}));
}