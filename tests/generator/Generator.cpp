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

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0.1};
  ParticleContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);
  EXPECT_EQ(p.size(), 4);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
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
  constexpr int dim = 2;

  std::vector dimensions = {1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, 1.0, 1.0, 0.1};
  ParticleContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 3d generation for Cuboids
*/
TEST(CuboidGenerator_3D, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 3;
  std::vector dimensions = {dim, dim, dim};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, distance, mass, 0.1};
  ParticleContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);
  EXPECT_EQ(p.size(), 27);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
    }
  }
}

/**
* Tests correctness of 3d applyMotion for Cuboids
*/
TEST(CuboidGenerator_3D, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  std::vector dimensions = {1, 1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.1};
  ParticleContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

/**
* Tests correctness of 2d generation for Spheres
*/
TEST(SphereGenerator_2D, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 2;
  int rad = 2;
  std::vector dimensions = {dim, dim};

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, rad, {0.0, 0.0}, distance, mass, 0.1};
  ParticleContainer<dim> pc{};

  Generator<SphereArgument<dim>, dim>::generate(s, pc);
  EXPECT_EQ(pc.size(), 13);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      ASSERT_TRUE(std::find_if(pc.getParticles().begin(), pc.getParticles().end(), [&s, &rad](const Particle<dim> &p) {
        return ArrayUtils::L2Norm(p.getX() - s.getCenterCoordinates()) > rad + 0.01 * s.getDistance();
      }) != pc.getParticles().end());
      EXPECT_EQ(pc.getParticles()[i].getM(), mass);
    }
  }
}

/**
* Tests correctness of 2d applyMotion for Spheres
*/
TEST(SpheresGenerator_2D, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, 1, {0.0, 0.0}, 1.0, 1.0, 0.1};
  ParticleContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 3d generation for Spheres
*/
TEST(SpheresGenerator_3D, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 3;
  int rad = 2;
  std::vector dimensions = {dim, dim};

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0, 0.0}, rad, {0.0, 0.0, 0.0}, distance, mass, 0.1};
  ParticleContainer<dim> pc{};

  Generator<SphereArgument<dim>, dim>::generate(s, pc);
  EXPECT_EQ(pc.size(), 33);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      ASSERT_TRUE(std::find_if(pc.getParticles().begin(), pc.getParticles().end(), [&s, &rad](const Particle<dim> &p) {
        return ArrayUtils::L2Norm(p.getX() - s.getCenterCoordinates()) > rad + 0.01 * s.getDistance();
      }) != pc.getParticles().end());
      EXPECT_EQ(pc.getParticles()[i].getM(), mass);
    }
  }
}

/**
* Tests correctness of 3d applyMotion for Spheres
*/
TEST(SpheresGenerator_3D, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0, 0.0}, 1, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.1};
  ParticleContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

