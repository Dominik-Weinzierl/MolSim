#include "gtest/gtest.h"
#include "particles/Particle.h"


/**
 * ensure that the velocity of a fixed particle is (and remains) zero
 */
TEST(FixedParticle_2D, velocity) {
  constexpr size_t dim = 2;
  Particle<dim> p = {{}, {3, 4}, 0, 0, 0, 0, true};
  EXPECT_EQ(p.getV()[0], 0);
  EXPECT_EQ(p.getV()[1], 0);
  p.setV({1, 2});
  EXPECT_EQ(p.getV()[0], 0);
  EXPECT_EQ(p.getV()[1], 0);
}

/**
 * ensure that the velocity of a fixed particle is (and remains) zero
 */
TEST(FixedParticle_3D, velocity) {
  constexpr size_t dim = 3;
  Particle<dim> p = {{}, {3, 4, 5}, 0, 0, 0, 0, true};
  EXPECT_EQ(p.getV()[0], 0);
  EXPECT_EQ(p.getV()[1], 0);
  EXPECT_EQ(p.getV()[2], 0);
  p.setV({1, 2, 3});
  EXPECT_EQ(p.getV()[0], 0);
  EXPECT_EQ(p.getV()[1], 0);
  EXPECT_EQ(p.getV()[2], 0);
}