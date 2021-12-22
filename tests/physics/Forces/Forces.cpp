#include <gtest/gtest.h>

#include "physics/DirectSum.h"
#include "physics/variants/Gravitation.h"
#include "physics/Forces/Forces.h"
#include "container/DirectSum/DirectSumContainer.h"

/**
 * ***************************************************
 * Test correct functionality of the Forces class
 * ******************************************+********
 */

/**
 * Test to check if the additional force actually acts on the particle
 */
TEST(Forces_2D, checkAdditionalGravitation) {
  const size_t dim = 2;
  double force = -9.81;

  DirectSum<Gravitation, dim> d{};
  DirectSumContainer<dim> c{};

  c.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});
  //std::cout << c.getParticles()[0].getF() << std::endl;
  d.calculateNextStep(c, 1.0, force);
  //std::cout << c.getParticles()[0].getF() << std::endl;
  Vector<dim> v{0.0, 0.0};

  ASSERT_TRUE(c.getParticles()[0].getF() != v);
}
