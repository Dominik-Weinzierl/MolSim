#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "physics/variants/LennardJones.h"
#include "container/LinkedCell/LinkedCellContainer.h"
#include "physics/LinkedCell.h"


/**
* Test if force remains unchanged if there is only one particle
*/

TEST(LCPhys2D, oneParticle) { // NOLINT(cert-err58-cpp)
  std::vector<BoundaryType>
      boundaries{BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow};
  std::array<int, 2> cellSize{1, 1};
  std::array<int, 2> domain{3, 3};
  double cutoffRadius = 2;
  LinkedCellContainer<2> container{boundaries, cellSize, domain, cutoffRadius};
  Vector<2> x{1, 1};
  Vector<2> v{0, 0};
  double m = 1;
  Particle p{x, v, m};
  container.addParticle(p);

  container.init();
  LinkedCell<LennardJones, 2> phy;
  phy.performUpdate(container);
  // we can do that here as v = 0.
  EXPECT_EQ(v, p.getF());
}

/**
 * Test if the force remains unchanged if two particles are too far away.
 */
TEST(LCPhys2D, twoParticlesFar) {
  std::vector<BoundaryType>
      boundaries{BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow};
  std::array<int, 2> cellSize{1, 1};
  std::array<int, 2> domain{3, 3};
  double cutoffRadius = 2;
  LinkedCellContainer<2> container{boundaries, cellSize, domain, cutoffRadius};
  Vector<2> x{0, 0};
  Vector<2> v{0, 0};
  double m = 1;
  Particle p{x, v, m};
  container.addParticle(p);

  Particle<2> q{{3, 3}, {0, 0}, 1};
  container.addParticle(q);

  container.init();
  LinkedCell<LennardJones, 2> phy;
  phy.performUpdate(container);
  // we can do that here as v = 0.
  EXPECT_EQ(v, p.getF());
  EXPECT_EQ(v, q.getF());
}
/**
 * Test if force is calculated correctly for two close particles
 */
TEST(LJPhys2D, twoParticlesClose) {
  std::vector<BoundaryType>
      boundaries{BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow};
  std::array<int, 2> cellSize{1, 1};
  std::array<int, 2> domain{8, 9};
  double cutoffRadius = 6;
  LinkedCellContainer<2> container{boundaries, cellSize, domain, cutoffRadius};
  container.addParticle({{2.0, 2.0}, {0.0, 0.0}, 1});

  // Particle 2
  container.addParticle({{0.0, 0.0}, {0.0, 0.0}, 1});

  container.init();
  Particle<2> particle_0 = container[0];
  Particle<2> particle_1 = container[1];
  LinkedCell<LennardJones, 2> l{};
  // Perform calculation
  l.performUpdate(container);

  // Check value of new force
  auto eps = std::numeric_limits<double>::epsilon() * 100;
  EXPECT_NEAR(container[0].getF()[0], -0.058364868164062458, eps);
  EXPECT_NEAR(container[0].getF()[1], -0.058364868164062458, eps);

  // Check value of new force
  EXPECT_NEAR(container[1].getF()[0], 0.058364868164062458, eps);
  EXPECT_NEAR(container[1].getF()[1], 0.058364868164062458, eps);
}

TEST(LCPhys3D, oneParticle) { // NOLINT(cert-err58-cpp)
  std::vector<BoundaryType> boundaries
      {BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow,
       BoundaryType::Outflow, BoundaryType::Outflow};
  std::array<int, 3> cellSize{1, 1, 1};
  std::array<int, 3> domain{3, 3, 3};
  double cutoffRadius = 2;
  LinkedCellContainer<3> container{boundaries, cellSize, domain, cutoffRadius};
  Vector<3> x{1, 1, 1};
  Vector<3> v{0, 0, 0};
  double m = 1;
  Particle p{x, v, m};
  container.addParticle(p);

  container.init();
  LinkedCell<LennardJones, 3> phy;
  phy.performUpdate(container);
  // we can do that here as v = 0.
  EXPECT_EQ(v, p.getF());
}

/**
 * Test if the force remains unchanged if two particles are too far away.
 */
TEST(LCPhys3D, twoParticlesFar) {
  std::vector<BoundaryType> boundaries
      {BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow,
       BoundaryType::Outflow, BoundaryType::Outflow};
  std::array<int, 3> cellSize{1, 1, 1};
  std::array<int, 3> domain{3, 3, 3};
  double cutoffRadius = 2;
  LinkedCellContainer<3> container{boundaries, cellSize, domain, cutoffRadius};
  Vector<3> x{1, 1, 1};
  Vector<3> v{0, 0, 0};
  double m = 1;
  Particle p{x, v, m};
  container.addParticle(p);
  Particle<3> q{{3, 3, 3}, {0, 0, 0}, 1};
  container.addParticle(q);

  container.init();
  LinkedCell<LennardJones, 3> phy;
  phy.performUpdate(container);
  // we can do that here as v = 0.
  EXPECT_EQ(v, p.getF());
  EXPECT_EQ(v, q.getF());
}
/**
 * Test if force is calculated correctly for two close particles
 */
TEST(LJPhys3D, twoParticlesClose) {
  std::vector<BoundaryType> boundaries
      {BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Outflow,
       BoundaryType::Outflow, BoundaryType::Outflow};
  std::array<int, 3> cellSize{1, 1, 1};
  std::array<int, 3> domain{9, 9, 9};
  double cutoffRadius = 2;
  LinkedCellContainer<3> container{boundaries, cellSize, domain, cutoffRadius};
  // Particle 1
  container.addParticle({{2.0, 2.0, 2.0}, {0.0, 0.0, 0.0}, 1});

  // Particle 2
  container.addParticle({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1});

  container.init();
  Particle<3> particle_0 = container[0];
  Particle<3> particle_1 = container[1];
  LinkedCell<LennardJones, 3> l{};
  // Perform calculation
  l.performUpdate(container);

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