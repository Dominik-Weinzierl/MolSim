#include <gtest/gtest.h>
#include <particles/ParticleContainer.h>
#include <physics/Physics.h>
#include "PhysicsFixture.h"


/**
 * ***************************************************
 * Test correct functionality of the class Physics
 * ******************************************+********
 */

/**
 * Test basic calculations of next steps. In this case, we test correct calculation of velocity.
 */
TEST_F(PhysicsFixture, calculateVelocityOfSunAndEarth) { // NOLINT(cert-err58-cpp)
  // Particle 0
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 2});

  // Particle 1
  container.addParticle({{0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}, 4});

  container[0].setF({0, 8.0, 0.0});
  container[1].setF({0.0, -8.0, 0.0});

  Particle particle_0 = container[0];
  Particle particle_1 = container[1];

  particle_0.setV({0.0, 2, 0.0});
  particle_1.setV({-1.0, -1.0, 0.0});

  // Perform calculation
  Physics<3>::calculateV(container, 1.0);

  EXPECT_EQ(container[0], particle_0);
  EXPECT_EQ(container[1], particle_1);
}

/**
 * Test basic calculations of next steps. In this case, we test correct calculation of positiob.
 */
TEST_F(PhysicsFixture, calculatePositionOfSunAndEarth) { // NOLINT(cert-err58-cpp)
  // Particle 0
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 2});

  // Particle 1
  container.addParticle({{0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}, 4});

  container[0].setF({0, 8.0, 0.0});
  container[1].setF({0.0, -8.0, 0.0});

  Particle particle_0 = container[0];
  Particle particle_1 = container[1];

  particle_0.setX({0.0, 2, 0.0});
  particle_1.setX({-1.0, -0.0, 0.0});

  // Perform calculation
  Physics<3>::calculateX(container, 1.0);

  EXPECT_EQ(container[0], particle_0);
  EXPECT_EQ(container[1], particle_1);
}