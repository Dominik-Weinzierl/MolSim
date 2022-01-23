#include <gtest/gtest.h>

#include "physics/DirectSum.h"
#include "physics/variants/Gravitation.h"
#include "container/DirectSum/DirectSumContainer.h"
#include "physics/Forces/Force.h"
#include "generator/GeneratorArguments/variants/CuboidArgument.h"
#include "physics/LinkedCell/LinkedCell.h"

/**
 * ***************************************************
 * Test correct functionality of the Forces class.
 * ******************************************+********
 */

/**
 * Tests if the additional force actually acts on the particle.
 */
TEST(Forces, checkAdditionalGravitation) { // NOLINT(cert-err58-cpp)
  const size_t dim = 2;
  Vector<dim> force{-9.81, 0};

  DirectSum<Gravitation, dim> d{};
  DirectSumContainer<dim> c{};
  Vector<dim> v{0.0, 0.0};

  c.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});
  d.calculateNextStep(c, 1.0, force, {});

  ASSERT_TRUE(c.getParticles()[0].getF() != v);
}

/**
 * Tests if additionalForce is only affective on the specific Particle.
 */
TEST(Forces, checkAdditionalForce){ // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, {2,2}, {0.0, 0.0}, 1.1225, 1.0, 0.1, true, 1, 5, 2, false,
                        std::vector<ForceContainer<dim>>{}};

  std::vector<BoundaryType>
      boundaries{BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow};
  Vector<2> cellSize{1, 1};
  Vector<2> domain{3, 3};
  double cutoffRadius = 2;
  LinkedCellContainer<2> p{boundaries, cellSize, domain, cutoffRadius};

  Generator<RectangularArgument<dim>, dim>::generate(c, p);

  Force<dim> force{{1.0, 1.0}, 0, 1};
  p.getParticles()[0].addAdditionalForce(force);

  LinkedCell<LennardJones, dim> physics{};
  Vector<dim> grav{0, 0};

  EXPECT_TRUE(p.getParticles()[0].getF() == grav);
  physics.calculateF(p, grav, 0);
  EXPECT_FALSE(p.getParticles()[0].getF() == grav);
}