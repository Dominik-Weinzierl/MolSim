#include <gtest/gtest.h>
#include "physics/variants/LennardJones.h"
#include "container/DirectSumContainer.h"
#include "physics/DirectSum.h"


/**
 * ***************************************************
 * Test correct functionality of the class LennardJones
 * ******************************************+********
 */

/**
 * Test basic calculations of next steps. In this case, we test the force between two particles with L2Norm is one.
 */
TEST(LennardJones_3D_DirectSumContainer, calculateForceBetweenTwoParticlesWithDistanceOne) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;
  DirectSum<LennardJones, dim> l{};
  DirectSumContainer<dim> container{};
  // Particle 1
  container.addParticle({{1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, 1});

  // Particle 2
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});

  Particle<dim> particle_0 = container[0];
  Particle<dim> particle_1 = container[1];

  // Perform calculation
  l.calculateF(container);

  // OldF should be zero
  EXPECT_TRUE(container[0].getOldF() == container[1].getOldF() && container[1].getOldF() == Vector<dim>{});
  // Mass should be unchanged
  EXPECT_TRUE(container[0].getM() == particle_0.getM() && container[1].getM() == particle_1.getM());
  // Velocity should be unchanged
  EXPECT_TRUE(container[0].getV() == particle_0.getV() && container[1].getV() == particle_1.getV());
  // Position should be unchanged
  EXPECT_TRUE(container[0].getX() == particle_0.getX() && container[1].getX() == particle_1.getX());
  // Type should be unchanged
  EXPECT_TRUE(container[0].getType() == particle_0.getType() && container[1].getType() == particle_1.getType());

  // Check value of new force
  auto eps = std::numeric_limits<double>::epsilon() * 100;
  EXPECT_NEAR(container[0].getF()[0], -1.37174211248285, eps);
  EXPECT_NEAR(container[0].getF()[1], -1.37174211248285, eps);
  EXPECT_NEAR(container[0].getF()[2], -1.37174211248285, eps);

  // Check value of new force
  EXPECT_NEAR(container[1].getF()[0], 1.37174211248285, eps);
  EXPECT_NEAR(container[1].getF()[1], 1.37174211248285, eps);
  EXPECT_NEAR(container[1].getF()[2], 1.37174211248285, eps);
}


/**
 * Test basic calculations of next steps. In this case, we test the force between two particles with L2Norm is not one.
 */
TEST(LennardJones_3D_DirectSumContainer, calculateForceBetweenTwoParticles) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;
  DirectSum<LennardJones, dim> l{};
  DirectSumContainer<dim> container{};
  // Particle 1
  container.addParticle({{2.0, 2.0, 2.0}, {0.0, 0.0, 0.0}, 1});

  // Particle 2
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});

  Particle<dim> particle_0 = container[0];
  Particle<dim> particle_1 = container[1];

  // Perform calculation
  l.calculateF(container);

  // OldF should be zero
  EXPECT_TRUE(container[0].getOldF() == container[1].getOldF() && container[1].getOldF() == Vector<dim>{});
  // Mass should be unchanged
  EXPECT_TRUE(container[0].getM() == particle_0.getM() && container[1].getM() == particle_1.getM());
  // Velocity should be unchanged
  EXPECT_TRUE(container[0].getV() == particle_0.getV() && container[1].getV() == particle_1.getV());
  // Position should be unchanged
  EXPECT_TRUE(container[0].getX() == particle_0.getX() && container[1].getX() == particle_1.getX());
  // Type should be unchanged
  EXPECT_TRUE(container[0].getType() == particle_0.getType() && container[1].getType() == particle_1.getType());

  // Check value of new force
  auto eps = std::numeric_limits<double>::epsilon() * 100;
  EXPECT_NEAR(container[0].getF()[0], -0.011560678155006872, eps);
  EXPECT_NEAR(container[0].getF()[1], -0.011560678155006872, eps);
  EXPECT_NEAR(container[0].getF()[2], -0.011560678155006872, eps);

  // Check value of new force
  EXPECT_NEAR(container[1].getF()[0], 0.011560678155006872, eps);
  EXPECT_NEAR(container[1].getF()[1], 0.011560678155006872, eps);
  EXPECT_NEAR(container[1].getF()[2], 0.011560678155006872, eps);
}

/**
 * Test basic calculations of next steps. In this case, we test the force between two particles with L2Norm is one.
 */
TEST(LennardJones_2D_DirectSumContainer, calculateForceBetweenTwoParticlesWithDistanceOne) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;
  DirectSum<LennardJones, dim> l{};
  DirectSumContainer<dim> container{};
  // Particle 1
  container.addParticle({{1.0, 1.0}, {0.0, 0.0}, 1});

  // Particle 2
  container.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});

  Particle<dim> particle_0 = container[0];
  Particle<dim> particle_1 = container[1];

  // Perform calculation
  l.calculateF(container);

  // OldF should be zero
  EXPECT_TRUE(container[0].getOldF() == container[1].getOldF() && container[1].getOldF() == Vector<dim>{});
  // Mass should be unchanged
  EXPECT_TRUE(container[0].getM() == particle_0.getM() && container[1].getM() == particle_1.getM());
  // Velocity should be unchanged
  EXPECT_TRUE(container[0].getV() == particle_0.getV() && container[1].getV() == particle_1.getV());
  // Position should be unchanged
  EXPECT_TRUE(container[0].getX() == particle_0.getX() && container[1].getX() == particle_1.getX());
  // Type should be unchanged
  EXPECT_TRUE(container[0].getType() == particle_0.getType() && container[1].getType() == particle_1.getType());

  // Check value of new force
  auto eps = std::numeric_limits<double>::epsilon() * 100;
  EXPECT_NEAR(container[0].getF()[0], -5.6249999999999973, eps);
  EXPECT_NEAR(container[0].getF()[1], -5.6249999999999973, eps);

  // Check value of new force
  EXPECT_NEAR(container[1].getF()[0], 5.6249999999999973, eps);
  EXPECT_NEAR(container[1].getF()[1], 5.6249999999999973, eps);
}


/**
 * Test basic calculations of next steps. In this case, we test the force between two particles with L2Norm is not one.
 */
TEST(LennardJones_2D_DirectSumContainer, calculateForceBetweenTwoParticles) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;
  DirectSum<LennardJones, dim> l{};
  DirectSumContainer<dim> container{};
  // Particle 1
  container.addParticle({{2.0, 2.0}, {0.0, 0.0}, 1});

  // Particle 2
  container.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});

  Particle<dim> particle_0 = container[0];
  Particle<dim> particle_1 = container[1];

  // Perform calculation
  l.calculateF(container);

  // OldF should be zero
  EXPECT_TRUE(container[0].getOldF() == container[1].getOldF() && container[1].getOldF() == Vector<dim>{});
  // Mass should be unchanged
  EXPECT_TRUE(container[0].getM() == particle_0.getM() && container[1].getM() == particle_1.getM());
  // Velocity should be unchanged
  EXPECT_TRUE(container[0].getV() == particle_0.getV() && container[1].getV() == particle_1.getV());
  // Position should be unchanged
  EXPECT_TRUE(container[0].getX() == particle_0.getX() && container[1].getX() == particle_1.getX());
  // Type should be unchanged
  EXPECT_TRUE(container[0].getType() == particle_0.getType() && container[1].getType() == particle_1.getType());

  // Check value of new force
  auto eps = std::numeric_limits<double>::epsilon() * 100;
  EXPECT_NEAR(container[0].getF()[0], -0.058364868164062458, eps);
  EXPECT_NEAR(container[0].getF()[1], -0.058364868164062458, eps);

  // Check value of new force
  EXPECT_NEAR(container[1].getF()[0], 0.058364868164062458, eps);
  EXPECT_NEAR(container[1].getF()[1], 0.058364868164062458, eps);
}


