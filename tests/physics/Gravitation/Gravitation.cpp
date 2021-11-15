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

  // Perform calculation
  Gravitation<3>::calculateF(container);

  // OldF should be zero
  EXPECT_TRUE(container[0].getOldF() == container[1].getOldF() && container[1].getOldF() == Vector<3>{});
  // Mass should be unchanged
  EXPECT_TRUE(container[0].getM() == planet_0.getM() && container[1].getM() == planet_1.getM());
  // Velocity should be unchanged
  EXPECT_TRUE(container[0].getV() == planet_0.getV() && container[1].getV() == planet_1.getV());
  // Position should be unchanged
  EXPECT_TRUE(container[0].getX() == planet_0.getX() && container[1].getX() == planet_1.getX());
  // Type should be unchanged
  EXPECT_TRUE(container[0].getType() == planet_0.getType() && container[1].getType() == planet_1.getType());

  // Check value of new force
  EXPECT_EQ(container[0].getF(), (Vector<3>{0, 8.0, 0.0}));
  EXPECT_EQ(container[1].getF(), (Vector<3>{0.0, -8.0, 0.0}));
}

/**
 * Test basic calculations of next steps. In this case, we test velocity of two planets.
 */
TEST_F(GravitationFixture, calculateVelocityOfSunAndEarth) { // NOLINT(cert-err58-cpp)
  // Planet 0
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 2});

  // Planet 1
  container.addParticle({{0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}, 4});

  container[0].setF({0, 8.0, 0.0});
  container[1].setF({0.0, -8.0, 0.0});

  Particle planet_0 = container[0];
  Particle planet_1 = container[1];

  // Perform calculation
  Gravitation<3>::calculateV(container, 1.0);

  // OldF should be unchanged
  EXPECT_TRUE(container[0].getOldF() == planet_0.getOldF() && container[1].getOldF() == planet_1.getOldF());
  // Mass should be unchanged
  EXPECT_TRUE(container[0].getM() == planet_0.getM() && container[1].getM() == planet_1.getM());
  // Force should be unchanged
  EXPECT_TRUE(container[0].getF() == planet_0.getF() && container[1].getF() == planet_1.getF());
  // Position should be unchanged
  EXPECT_TRUE(container[0].getX() == planet_0.getX() && container[1].getX() == planet_1.getX());
  // Type should be unchanged
  EXPECT_TRUE(container[0].getType() == planet_0.getType() && container[1].getType() == planet_1.getType());

  // Check value of new velocity
  EXPECT_EQ(container[0].getV(), (Vector<3>{0.0, 2, 0.0}));
  EXPECT_EQ(container[1].getV(), (Vector<3>{-1.0, -1.0, 0.0}));
}

/**
 * Test basic calculations of next steps. In this case, we test the position calculations of two planets.
 */
TEST_F(GravitationFixture, calculatePositionOfSunAndEarth) { // NOLINT(cert-err58-cpp)
  // Planet 0
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 2});

  // Planet 1
  container.addParticle({{0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}, 4});

  container[0].setF({0, 8.0, 0.0});
  container[1].setF({0.0, -8.0, 0.0});

  Particle planet_0 = container[0];
  Particle planet_1 = container[1];

  // Perform calculation
  Gravitation<3>::calculateX(container, 1.0);

  // OldF should be unchanged
  EXPECT_TRUE(container[0].getOldF() == planet_0.getOldF() && container[1].getOldF() == planet_1.getOldF());
  // Mass should be unchanged
  EXPECT_TRUE(container[0].getM() == planet_0.getM() && container[1].getM() == planet_1.getM());
  // Force should be unchanged
  EXPECT_TRUE(container[0].getF() == planet_0.getF() && container[1].getF() == planet_1.getF());
  // Velocity should be unchanged
  EXPECT_TRUE(container[0].getV() == planet_0.getV() && container[1].getV() == planet_1.getV());
  // Type should be unchanged
  EXPECT_TRUE(container[0].getType() == planet_0.getType() && container[1].getType() == planet_1.getType());

  // Check value of new velocity
  EXPECT_EQ(container[0].getX(), (Vector<3>{0.0, 2, 0.0}));
  EXPECT_EQ(container[1].getX(), (Vector<3>{-1.0, -0.0, 0.0}));
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

  // New force is unchanged
  EXPECT_EQ(container[0].getF(), sun.getF());
  // OldF is unchanged
  EXPECT_EQ(container[0].getOldF(), sun.getOldF());
  // New velocity is unchanged
  EXPECT_EQ(container[0].getV(), sun.getV());
  // New position is unchanged
  EXPECT_EQ(container[0].getX(), sun.getX());
  // Type is unchanged
  EXPECT_EQ(container[0].getType(), sun.getType());
  // Mass is unchanged
  EXPECT_EQ(container[0].getM(), sun.getM());
}
