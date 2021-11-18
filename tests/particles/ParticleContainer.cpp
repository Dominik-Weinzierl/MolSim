#include <gtest/gtest.h>
#include "particles/ParticleContainer.h"
#include "particles/Particle.h"

/**
 * ***********************************************************
 * Test correct functionality of the class ParticleContainer.
 * ******************************************+****************
*/

/**
 * Tests correctness of constructors of the ParticleContainer.
 */
TEST(ParticleContainer_3D, constructor) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  ParticleContainer<dim> p1{};
  p1.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});

  //Tests the "vector"-constructor
  std::vector<Particle<dim>> v1{{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1}};
  ParticleContainer p2(v1);
  EXPECT_EQ(p1.size(), p2.size());
  EXPECT_EQ(p1, p2);

  //Tests the copy constructor
  ParticleContainer p3(p1);
  EXPECT_EQ(p1.size(), p3.size());
  EXPECT_EQ(p1, p3);
}

/**
 * Tests correctness of addParticle-Method of the ParticleContainer.
 */
TEST(ParticleContainer_3D, addParticle) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  std::vector<Particle<dim>> v1{{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1}};
  ParticleContainer<dim> p1{v1};
  ParticleContainer<dim> p2{};
  p2.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});

  EXPECT_EQ(p1.size(), p2.size());
}

/**
 * Tests correctness of the size-Method of the ParticleContainer.
 */
TEST(ParticleContainer_3D, size) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  ParticleContainer<dim> p1{};
  EXPECT_EQ(p1.size(), 0);
  p1.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});
  p1.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});
  EXPECT_EQ(p1.size(), 2);
  p1.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});
  EXPECT_EQ(p1.size(), 3);
}

/**
 * Tests correctness of constructors of the ParticleContainer.
 */
TEST(ParticleContainer_2D, constructor) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  ParticleContainer<dim> p1{};
  p1.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});

  //Tests the "vector"-constructor
  std::vector<Particle<dim>> v1{{{0.0, 0.0}, {0.0, 0.0}, 1}};
  ParticleContainer p2(v1);
  EXPECT_EQ(p1.size(), p2.size());
  EXPECT_EQ(p1, p2);

  //Tests the copy constructor
  ParticleContainer p3(p1);
  EXPECT_EQ(p1.size(), p3.size());
  EXPECT_EQ(p1, p3);
}

/**
 * Tests correctness of addParticle-Method of the ParticleContainer.
 */
TEST(ParticleContainer_2D, addParticle) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  std::vector<Particle<dim>> v1{{{0.0, 0.0}, {0.0, 0.0}, 1}};
  ParticleContainer<dim> p1{v1};
  ParticleContainer<dim> p2{};
  p2.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});

  EXPECT_EQ(p1.size(), p2.size());
}

/**
 * Tests correctness of the size-Method of the ParticleContainer.
 */
TEST(ParticleContainer_2D, size) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  ParticleContainer<dim> p1{};
  EXPECT_EQ(p1.size(), 0);
  p1.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});
  p1.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});
  EXPECT_EQ(p1.size(), 2);
  p1.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});
  EXPECT_EQ(p1.size(), 3);
}

