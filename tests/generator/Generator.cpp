#include <gtest/gtest.h>
#include "generator/Generator.h"
#include "generator/GeneratorArguments/CuboidArgument.h"
#include "generator/GeneratorArguments/SphereArgument.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "particles/Particle.h"

/**
 * ***************************************************
 * Test correct functionality of the Generator-class.
 * ******************************************+********
 */

/**
* Tests correctness of 2d generation for Cuboids
*/
TEST(CuboidGenerator_2D, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 2;
  std::vector dimensions = {dim, dim};

  CuboidArgument c1{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0.1};
  ParticleContainer<dim> p{};

  Generator<CuboidArgument<dim>,dim>::generate(c1, p);
  EXPECT_EQ(p.size(), 4);

  for(unsigned long i = 0; i < dim; i++){
    for(auto j = 0; j < dim; j++){
      Vector<dim> pos {static_cast<double>(i)*distance, static_cast<double>(j)*distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos] (const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
    }
  }
}

/**
* Tests correctness of 2d applyMotion for Cuboids
*/
TEST(CuboidGenerator_2D, applyMotion) { // NOLINT(cert-err58-cpp)
  //Vector<2> maxwellBoltzmann = maxwellBoltzmannDistributedVelocity<2>(0.1);

}

/**
* Tests correctness of 3d generation for Cuboids
*/
TEST(CuboidGenerator_3D, generate) { // NOLINT(cert-err58-cpp)

}

/**
* Tests correctness of 3d applyMotion for Cuboids
*/
TEST(CuboidGenerator_3D, applyMotion) { // NOLINT(cert-err58-cpp)
}

/**
* Tests correctness of 2d generation for Spheres
*/
TEST(SphereGenerator_2D, generate) { // NOLINT(cert-err58-cpp)

}

/**
* Tests correctness of 2d applyMotion for Spheres
*/
TEST(SpheresGenerator_2D, applyMotion) { // NOLINT(cert-err58-cpp)

}

/**
* Tests correctness of 3d generation for Spheres
*/
TEST(SpheresGenerator_3D, generate) { // NOLINT(cert-err58-cpp)

}

/**
* Tests correctness of 3d applyMotion for Spheres
*/
TEST(SpheresGenerator_3D, applyMotion) { // NOLINT(cert-err58-cpp)

}

