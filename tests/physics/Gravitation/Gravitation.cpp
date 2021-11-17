#include <gtest/gtest.h>
#include "GravitationFixture.h"


/**
 * ***************************************************
 * Test correct functionality of the class Gravitation
 * ******************************************+********
 */

/**
 * Test basic calculations of next steps. In this case, we test the force between two planets.
 */
TEST_F(GravitationFixture, calculateForceBetweenSunAndEarth) { // NOLINT(cert-err58-cpp)
  // Planet 0
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 2});

  // Planet 1
  container.addParticle({{0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}, 4});

  Particle planet_0 = container[0];
  Particle planet_1 = container[1];

  planet_0.setF(Vector<3>{0, 8.0, 0.0});
  planet_1.setF(Vector<3>{0.0, -8.0, 0.0});

  // Perform calculation
  Gravitation<3>::calculateF(container);

  EXPECT_EQ(container[0], planet_0);
  EXPECT_EQ(container[1], planet_1);
}

/**
 * Test basic calculations of next steps. In this case, we test that the force,
 * velocity and position is unchanged for an single non moving planet.
 */
TEST_F(GravitationFixture, calculateNextStepWithSinglePlanetWithoutMoving) { // NOLINT(cert-err58-cpp)
  // Add the sun
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});

  Particle sun = container[0];

  // Perform calculation
  Gravitation<3>::calculateNextStep(container, 1.0);

  EXPECT_EQ(container[0], sun);
}
