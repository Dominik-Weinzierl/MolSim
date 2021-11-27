#include <gtest/gtest.h>
#include "physics/Gravitation/Gravitation.h"
#include "particles/ParticleContainer/ParticleContainer.h"


/**
 * ***************************************************
 * Test correct functionality of the class Gravitation
 * ******************************************+********
 */

/**
 * Test basic calculations of next steps. In this case, we test the force between two planets.
 */
TEST(Gravitation_3D, calculateForceBetweenSunAndEarth) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;
  Gravitation<dim> g{};
  ParticleContainer<dim> container{};
  // Planet 0
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 2});

  // Planet 1
  container.addParticle({{0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}, 4});

  Particle<dim> planet_0 = container[0];
  Particle<dim> planet_1 = container[1];

  planet_0.setF({0, 8.0, 0.0});
  planet_1.setF({0.0, -8.0, 0.0});

  // Perform calculation
  g.calculateF(container);

  EXPECT_EQ(container[0], planet_0);
  EXPECT_EQ(container[1], planet_1);
}

/**
 * Test basic calculations of next steps. In this case, we test that the force,
 * velocity and position is unchanged for an single non moving planet.
 */
TEST(Gravitation_3D, calculateNextStepWithSinglePlanetWithoutMoving) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;
  Gravitation<dim> g{};
  ParticleContainer<dim> container{};
  // Add the sun
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});

  Particle sun = container[0];

  // Perform calculation
  g.calculateNextStep(container, 1.0);

  EXPECT_EQ(container[0], sun);
}

/**
 * Test basic calculations of next steps. In this case, we test the force between two planets.
 */
TEST(Gravitation_2D, calculateForceBetweenSunAndEarth) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;
  Gravitation<dim> g{};
  ParticleContainer<dim> container{};
  // Planet 0
  container.addParticle({{0.0, 0.0}, {0.0, 0.0}, 2});

  // Planet 1
  container.addParticle({{0.0, 1.0}, {-1.0, 0.0}, 4});

  Particle<dim> planet_0 = container[0];
  Particle<dim> planet_1 = container[1];

  planet_0.setF({0, 8.0});
  planet_1.setF({0.0, -8.0});

  // Perform calculation
  g.calculateF(container);

  EXPECT_EQ(container[0], planet_0);
  EXPECT_EQ(container[1], planet_1);
}

/**
 * Test basic calculations of next steps. In this case, we test that the force,
 * velocity and position is unchanged for an single non moving planet.
 */
TEST(Gravitation_2D, calculateNextStepWithSinglePlanetWithoutMoving) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;
  Gravitation<dim> g{};
  ParticleContainer<dim> container{};
  // Add the sun
  container.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});

  Particle sun = container[0];

  // Perform calculation
  g.calculateNextStep(container, 1.0);

  EXPECT_EQ(container[0], sun);
}

