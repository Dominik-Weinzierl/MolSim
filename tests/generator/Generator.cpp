#include <gtest/gtest.h>

#include "generator/Generator.h"
#include "generator/GeneratorArguments/CuboidArgument.h"
#include "generator/GeneratorArguments/SphereArgument.h"
#include "particles/Particle.h"
#include "container/DirectSum/DirectSumContainer.h"

/**
 * ***************************************************
 * Test correct functionality of the Generator-class.
 * ******************************************+********
 */

/**
* Tests correctness of 2d generation for Cuboids.
*/
TEST(CuboidGenerator_2D_DirectSumContainer, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 2;
  std::array<int, dim> dimensions = {dim, dim};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0.1};
  DirectSumContainer<dim> p{};

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
 * Test if non-packed 2D Cuboids are generated correctly.
 */
TEST(CuboidGenerator_2D_DirectSumContainer, generateUnpacked) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 2;
  std::array<int, dim> dimensions = {4, 4};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0.1, false};
  DirectSumContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);
  EXPECT_EQ(p.size(), 12);

  for (unsigned long i = 0; i < 4; i++) {
    for (auto j = 0; j < 4; j += 4) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
    }
  }

  for (unsigned long i = 0; i < 4; i += 4) {
    for (auto j = 0; j < 4; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
    }
  }

  for (unsigned long i = 1; i < 3; i++) {
    for (auto j = 1; j < 3; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_FALSE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
    }
  }
}


/**
 * Test if non-packed 3D Cuboids are generated correctly.
 */
TEST(CuboidGenerator_3D_DirectSumContainer, generateUnpacked) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 3;
  std::array<int, dim> dimensions = {4, 4, 4};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0.1, false};
  DirectSumContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);
  EXPECT_EQ(p.size(), 56);

  for (unsigned long i = 0; i < 4; i++) {
    for (auto j = 0; j < 4; j += 4) {
      for (auto k = 0; k < 4; k++) {
        Vector<dim> pos
            {static_cast<double>(i) * distance, static_cast<double>(j) * distance, static_cast<double>(k) * distance};
        ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
          return p1.getX() == pos;
        }) != p.getParticles().end());
      }
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
    }
  }

  for (unsigned long i = 0; i < 4; i += 4) {
    for (auto j = 0; j < 4; j++) {
      for (auto k = 0; k < 4; k++) {
        Vector<dim> pos
            {static_cast<double>(i) * distance, static_cast<double>(j) * distance, static_cast<double>(k) * distance};
        ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
          return p1.getX() == pos;
        }) != p.getParticles().end());
      }
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
    }
  }

  for (unsigned long i = 0; i < 4; i++) {
    for (auto j = 0; j < 4; j++) {
      for (auto k = 0; k < 4; k += 4) {
        Vector<dim> pos
            {static_cast<double>(i) * distance, static_cast<double>(j) * distance, static_cast<double>(k) * distance};
        ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
          return p1.getX() == pos;
        }) != p.getParticles().end());
      }
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
    }
  }

  for (unsigned long i = 1; i < 3; i++) {
    for (auto j = 1; j < 3; j++) {
      for (auto k = 1; k < 3; k++) {
        Vector<dim> pos
            {static_cast<double>(i) * distance, static_cast<double>(j) * distance, static_cast<double>(k) * distance};
        ASSERT_FALSE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
          return p1.getX() == pos;
        }) != p.getParticles().end());
      }
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
    }
  }
}



/**
* Tests correctness of 2d applyMotion for Cuboids.
*/
TEST(CuboidGenerator_2D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  std::array<int, dim> dimensions = {1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, 1.0, 1.0, 0.1};
  DirectSumContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 2d applyMotion for Cuboids.
*/
TEST(CuboidGenerator_2D_DirectSumContainer, applyNoMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  std::array<int, dim> dimensions = {1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, 1.0, 1.0, 0.0};
  DirectSumContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 3d generation for Cuboids.
*/
TEST(CuboidGenerator_3D_DirectSumContainer, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 3;
  std::array<int, dim> dimensions = {dim, dim, dim};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, distance, mass, 0.1};
  DirectSumContainer<dim> p{};

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
* Tests correctness of 3d applyMotion for Cuboids.
*/
TEST(CuboidGenerator_3D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  std::array<int, dim> dimensions = {1, 1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.1};
  DirectSumContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

/**
* Tests correctness of 3d applyMotion for Cuboids.
*/
TEST(CuboidGenerator_3D_DirectSumContainer, applyNoMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  std::array<int, dim> dimensions = {1, 1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.0};
  DirectSumContainer<dim> p{};

  Generator<CuboidArgument<dim>, dim>::generate(c, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

/**
* Tests correctness of 2d generation for Spheres.
*/
TEST(SphereGenerator_2D_DirectSumContainer, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 2;
  int rad = 2;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, rad, {0.0, 0.0}, distance, mass, 0.1};
  DirectSumContainer<dim> pc{};

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
* Tests correctness of 2d generation for unpacked Spheres.
*/
TEST(SphereGenerator_2D_DirectSumContainer, generateUnpacked) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 2;
  int rad = 2;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, rad, {0.0, 0.0}, distance, mass, 0.1, false};
  DirectSumContainer<dim> pc{};

  Generator<SphereArgument<dim>, dim>::generate(s, pc);
  EXPECT_EQ(pc.size(), 8);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      ASSERT_TRUE(std::find_if(pc.getParticles().begin(), pc.getParticles().end(), [&s, &rad](const Particle<dim> &p) {
        return (ArrayUtils::L2Norm(p.getX() - s.getCenterCoordinates()) > rad + 0.01 * s.getDistance()
            || ArrayUtils::L2Norm(p.getX() - s.getCenterCoordinates()) < rad + 0.6 * s.getDistance());
      }) != pc.getParticles().end());
      EXPECT_EQ(pc.getParticles()[i].getM(), mass);
    }
  }
}

/**
* Tests correctness of 2d applyMotion for Spheres.
*/
TEST(SpheresGenerator_2D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, 1, {0.0, 0.0}, 1.0, 1.0, 0.1};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 2d applyMotion for Spheres.
*/
TEST(SpheresGenerator_2D_DirectSumContainer, applyNoMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, 1, {0.0, 0.0}, 1.0, 1.0, 0.0};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 3d generation for Spheres.
*/
TEST(SpheresGenerator_3D_DirectSumContainer, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 3;
  int rad = 2;
  std::vector dimensions = {dim, dim};

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0, 0.0}, rad, {0.0, 0.0, 0.0}, distance, mass, 0.1};
  DirectSumContainer<dim> pc{};

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
* Tests correctness of 3d generation for unpacked Spheres.
*/
TEST(SpheresGenerator_3D_DirectSumContainer, generateUnpacked) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 3;
  int rad = 2;
  std::vector dimensions = {dim, dim};

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0, 0.0}, rad, {0.0, 0.0, 0.0}, distance, mass, 0.1, false};
  DirectSumContainer<dim> pc{};

  Generator<SphereArgument<dim>, dim>::generate(s, pc);
  EXPECT_EQ(pc.size(), 26);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      ASSERT_TRUE(std::find_if(pc.getParticles().begin(), pc.getParticles().end(), [&s, &rad](const Particle<dim> &p) {
        return (ArrayUtils::L2Norm(p.getX() - s.getCenterCoordinates()) > rad + 0.01 * s.getDistance()
            || ArrayUtils::L2Norm(p.getX() - s.getCenterCoordinates()) < rad + 0.6 * s.getDistance());
      }) != pc.getParticles().end());
      EXPECT_EQ(pc.getParticles()[i].getM(), mass);
    }
  }
}

/**
* Tests correctness of 3d applyMotion for Spheres.
*/
TEST(SpheresGenerator_3D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0, 0.0}, 1, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.1};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

/**
* Tests correctness of 3d applyMotion for Spheres.
*/
TEST(SpheresGenerator_3D_DirectSumContainer, applyZeroMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0, 0.0}, 1, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.0};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

