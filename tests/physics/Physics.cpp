#include <gtest/gtest.h>
#include <particles/ParticleContainer.h>
#include <physics/Physics.h>


/**
 * ***************************************************
 * Test correct functionality of the class Physics.
 * ******************************************+********
 */

/**
 * Test basic calculations of next steps. In this case, we test correct calculation of velocity.
 */
TEST(Physics_3D, calculateVelocity) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;
  ParticleContainer<dim> container{};
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 2});

  container[0].setF({0, 8.0, 0.0});

  Particle<dim> particle_0 = container[0];

  particle_0.setV({0.0, 2, 0.0});

  // Perform calculation
  Physics<dim>::calculateV(container, 1.0);

  EXPECT_EQ(container[0], particle_0);
}

/**
 * Test basic calculations of next steps. In this case, we test correct calculation of positiob.
 */
TEST(Physics_3D, calculatePosition) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;
  ParticleContainer<dim> container{};
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 2});

  container[0].setF({0, 8.0, 0.0});

  Particle<dim> particle_0 = container[0];

  particle_0.setX({0.0, 2, 0.0});

  // Perform calculation
  Physics<dim>::calculateX(container, 1.0);

  EXPECT_EQ(container[0], particle_0);
}

/**
 * Test basic calculations of next steps. In this case, we test correct calculation of velocity.
 */
TEST(Physics_2D, calculateVelocity) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;
  ParticleContainer<dim> container{};
  container.addParticle({{0.0, 0.0}, {0.0, 0.0}, 2});

  container[0].setF({0, 8.0});

  Particle<dim> particle_0 = container[0];

  particle_0.setV({0.0, 2});

  // Perform calculation
  Physics<dim>::calculateV(container, 1.0);

  EXPECT_EQ(container[0], particle_0);
}

/**
 * Test basic calculations of next steps. In this case, we test correct calculation of positiob.
 */
TEST(Physics_2D, calculatePosition) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;
  ParticleContainer<dim> container{};
  container.addParticle({{0.0, 0.0}, {0.0, 0.0}, 2});

  container[0].setF({0, 8.0});

  Particle<dim> particle_0 = container[0];

  particle_0.setX({0.0, 2});

  // Perform calculation
  Physics<dim>::calculateX(container, 1.0);

  EXPECT_EQ(container[0], particle_0);
}