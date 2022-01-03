#include <gtest/gtest.h>

#include "physics/DirectSum.h"
#include "physics/variants/Gravitation.h"
#include "physics/Forces/Forces.h"
#include "container/DirectSum/DirectSumContainer.h"

/**
 * ***************************************************
 * Test correct functionality of the Forces class.
 * ******************************************+********
 */

/**
 * Test to check if the additional force actually acts on the particle.
 */
TEST(Forces, checkAdditionalGravitation) {
  const size_t dim = 2;
  Vector<dim> force{-9.81, 0};

  DirectSum<Gravitation, dim> d{};
  DirectSumContainer<dim> c{};
  Vector<dim> v{0.0, 0.0};

  c.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});
  d.calculateNextStep(c, 1.0, force);

  ASSERT_TRUE(c.getParticles()[0].getF() != v);
}
