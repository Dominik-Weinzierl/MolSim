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
TEST(ParticleContainer, constructor){ // NOLINT(cert-err58-cpp)
  ParticleContainer<3> p1{};
  p1.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});

  //Tests the "vector"-constructor
  std::vector<Particle<3>> v1{{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1}};
  ParticleContainer p2 (v1);
  EXPECT_EQ(p1.size(), p2.size());
  EXPECT_EQ(p1, p2);

  //Tests the copy constructor
  ParticleContainer p3 (p1);
  EXPECT_EQ(p1.size(), p3.size());
  EXPECT_EQ(p1, p3);
}

/**
 * Tests correctness of addParticle-Method of the ParticleContainer.
 */
TEST(ParticleContainer, addParticle){ // NOLINT(cert-err58-cpp)
  std::vector<Particle<3>> v1{{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1}};
  ParticleContainer<3> p1{v1};
  ParticleContainer<3> p2{};
  p2.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});

  EXPECT_EQ(p1.size(), p2.size());
}

/**
 * Tests correctness of the size-Method of the ParticleContainer.
 */
TEST(ParticleContainer, size){ // NOLINT(cert-err58-cpp)
  ParticleContainer<3> p1{};
  EXPECT_EQ(p1.size(), 0);
  p1.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});
  p1.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});
  EXPECT_EQ(p1.size(), 2);
  p1.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});
  EXPECT_EQ(p1.size(), 3);
}
