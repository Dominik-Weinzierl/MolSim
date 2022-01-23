#include <gtest/gtest.h>

#include "generator/Generator.h"
#include "generator/GeneratorArguments/variants/CuboidArgument.h"
#include "generator/GeneratorArguments/SphereArgument.h"
#include "generator/GeneratorArguments/RectangularArgument.h"
#include "particles/Particle.h"
#include "container/DirectSum/DirectSumContainer.h"

/**
 * ***************************************************
 * Test correct functionality of the Generator-class.
 * ******************************************+********
 */


//----------------------------------------Cuboid----------------------------------------

/**
* Tests correctness of 2d generation for Cuboids, 2D.
*/
TEST(CuboidGenerator_2D_DirectSumContainer, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 2;
  std::array<int, dim> dimensions = {dim, dim};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0.1, true, 1, 5, 2, true,
                        std::vector<ForceContainer<dim>>{}};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(c, p);
  EXPECT_EQ(p.size(), 4);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), c.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), c.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), c.getDepthOfPotentialWell());
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

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0.1, false, 1, 5, 2, true,
                        std::vector<ForceContainer<dim>>{}};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(c, p);
  EXPECT_EQ(p.size(), 12);

  for (unsigned long i = 0; i < 4; i++) {
    for (auto j = 0; j < 4; j += 4) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), c.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), c.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), c.getDepthOfPotentialWell());
    }
  }

  for (unsigned long i = 0; i < 4; i += 4) {
    for (auto j = 0; j < 4; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), c.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), c.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), c.getDepthOfPotentialWell());
    }
  }

  for (unsigned long i = 1; i < 3; i++) {
    for (auto j = 1; j < 3; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_FALSE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), c.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), c.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), c.getDepthOfPotentialWell());
    }
  }
}

/**
* Tests correctness of 3D generation for Cuboids.
*/
TEST(CuboidGenerator_3D_DirectSumContainer, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 3;
  std::array<int, dim> dimensions = {dim, dim, dim};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0.1, true, 1, 5, 2, true,
                        std::vector<ForceContainer<dim>>{}};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(c, p);
  EXPECT_EQ(p.size(), 27);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), c.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), c.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), c.getDepthOfPotentialWell());
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

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0.1, false, 1, 5, 2, true,
                        std::vector<ForceContainer<dim>>{}};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(c, p);
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
      EXPECT_EQ(p.getParticles()[i].getType(), c.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), c.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), c.getDepthOfPotentialWell());
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
      EXPECT_EQ(p.getParticles()[i].getType(), c.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), c.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), c.getDepthOfPotentialWell());
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
      EXPECT_EQ(p.getParticles()[i].getType(), c.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), c.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), c.getDepthOfPotentialWell());
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
      EXPECT_EQ(p.getParticles()[i].getType(), c.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), c.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), c.getDepthOfPotentialWell());
    }
  }
}

/**
* Tests correctness of 2d applyMotion for Cuboids.
*/
TEST(CuboidGenerator_2D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  std::array<int, dim> dimensions = {1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, 1.0, 1.0, 0.1, true, 1, 5, 2, false,
                        std::vector<ForceContainer<dim>>{}};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(c, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 2d applyMotion for Cuboids.
*/
TEST(CuboidGenerator_2D_DirectSumContainer, applyNoMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  std::array<int, dim> dimensions = {1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, 1.0, 1.0, 0.0, true, 1, 5, 2, false,
                        std::vector<ForceContainer<dim>>{}};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(c, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 3d applyMotion for Cuboids.
*/
TEST(CuboidGenerator_3D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  std::array<int, dim> dimensions = {1, 1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.1, true, 1, 5, 2, false,
                        std::vector<ForceContainer<dim>>{}};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(c, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

/**
* Tests correctness of 3d applyMotion for Cuboids.
*/
TEST(CuboidGenerator_3D_DirectSumContainer, applyNoMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  std::array<int, dim> dimensions = {1, 1, 1};

  CuboidArgument<dim> c{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.0, true, 1, 5, 2, false,
                        std::vector<ForceContainer<dim>>{}};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(c, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

//----------------------------------------Membrane----------------------------------------

/**
* Tests correctness of 2d generation for Membranes.
*/
TEST(MembraneGenerator_2D_DirectSumContainer, generate) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;
  double distance = 2.2;
  double mass = 1.0;
  std::array<int, dim> dimensions = {dim, dim};

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0, true, 1, 1, 2, 2.2, 300, true,
                          std::vector<ForceContainer<dim>>{}, true};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);
  EXPECT_EQ(p.size(), 4);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), m.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), m.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), m.getDepthOfPotentialWell());
    }
  }
}

/**
 * Test if non-packed 2D Membranes are generated correctly.
 */
TEST(MembraneGenerator_2D_DirectSumContainer, generateUnpacked) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;
  double distance = 2.2;
  double mass = 1.0;
  std::array<int, dim> dimensions = {4, 4};

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, distance, mass, 0, false, 1, 1, 2, 2.2, 300, true,
                          std::vector<ForceContainer<dim>>{}, true};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);
  EXPECT_EQ(p.size(), 12);

  for (unsigned long i = 0; i < 4; i++) {
    for (auto j = 0; j < 4; j += 4) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), m.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), m.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), m.getDepthOfPotentialWell());
    }
  }

  for (unsigned long i = 0; i < 4; i += 4) {
    for (auto j = 0; j < 4; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), m.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), m.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), m.getDepthOfPotentialWell());
    }
  }

  for (unsigned long i = 1; i < 3; i++) {
    for (auto j = 1; j < 3; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_FALSE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), m.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), m.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), m.getDepthOfPotentialWell());
    }
  }
}

/**
* Tests correctness of 3d generation for Membranes.
*/
TEST(MembraneGenerator_3D_DirectSumContainer, generate) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;
  double distance = 2.2;
  double mass = 1.0;
  std::array<int, dim> dimensions = {dim, dim, dim};

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, distance, mass, 0, true, 1, 1, 2, 2.2, 300, true,
                          std::vector<ForceContainer<dim>>{}, true};

  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);
  EXPECT_EQ(p.size(), 27);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      Vector<dim> pos{static_cast<double>(i) * distance, static_cast<double>(j) * distance};
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&pos](const Particle<dim> &p1) {
        return p1.getX() == pos;
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), m.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), m.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), m.getDepthOfPotentialWell());
    }
  }
}

/**
 * Test if non-packed 3D Membranes are generated correctly.
 */
TEST(MembraneGenerator_3D_DirectSumContainer, generateUnpacked) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;
  double distance = 2.2;
  double mass = 1.0;
  std::array<int, dim> dimensions = {4, 4, 4};

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, distance, mass, 0, false, 1, 1, 2, 2.2, 300, true,
                          std::vector<ForceContainer<dim>>{}, true};

  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);
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
      EXPECT_EQ(p.getParticles()[i].getType(), m.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), m.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), m.getDepthOfPotentialWell());
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
      EXPECT_EQ(p.getParticles()[i].getType(), m.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), m.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), m.getDepthOfPotentialWell());
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
      EXPECT_EQ(p.getParticles()[i].getType(), m.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), m.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), m.getDepthOfPotentialWell());
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
      EXPECT_EQ(p.getParticles()[i].getType(), m.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), m.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), m.getDepthOfPotentialWell());
    }
  }
}

/**
* Tests correctness of 2d applyMotion for Membranes.
*/
TEST(MemrbaneGenerator_2D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  std::array<int, dim> dimensions = {1, 1};

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, 1.0, 1.0, 0.1, true, 1, 1, 2, 2.2, 300, false,
                          std::vector<ForceContainer<dim>>{}, false};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 2d applyMotion for Membranes.
*/
TEST(MembraneGenerator_2D_DirectSumContainer, applyNoMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  std::array<int, dim> dimensions = {1, 1};

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0}, dimensions, {0.0, 0.0}, 1.0, 1.0, 0, true, 1, 1, 2, 2.2, 300, false,
                          std::vector<ForceContainer<dim>>{}, false};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 3d applyMotion for Membranes.
*/
TEST(MembraneGenerator_3D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  std::array<int, dim> dimensions = {1, 1, 1};

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.1, true, 1, 1, 2, 2.2, 300, false,
                          std::vector<ForceContainer<dim>>{}, false};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

/**
* Tests correctness of 3d applyMotion for Membranes.
*/
TEST(MembraneGenerator_3D_DirectSumContainer, applyNoMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  std::array<int, dim> dimensions = {1, 1, 1};

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0, 0.0}, dimensions, {0.0, 0.0, 0.0}, 1.0, 1.0, 0, true, 1, 1, 2, 2.2, 300, false,
                          std::vector<ForceContainer<dim>>{}, false};
  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

/**
 * Tests correctness of getPositionInContainer-Method 2D.
 */
TEST(Membrane_Generator_2D_DirectSumContainer, getPositionInContainer){ // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0}, {2,2}, {0.0, 0.0}, 1.0, 1.0, 0, true, 1, 1, 2, 2.2, 300, false,
                          std::vector<ForceContainer<dim>>{}, false};

  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);

  int p0 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0,0}, 0, m);
  int p1 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0,1}, 0, m);
  int p2 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1,0}, 0, m);
  int p3 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1,1}, 0, m);

  EXPECT_EQ(p0, 0);
  EXPECT_EQ(p1, 1);
  EXPECT_EQ(p2, 2);
  EXPECT_EQ(p3, 3);
}

/**
 * Tests correctness of getPositionInContainer-Method 3D.
 */
TEST(Membrane_Generator_3D_DirectSumContainer, getPositionInContainer){ // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0, 0.0}, {2,2,2}, {0.0, 0.0, 0.0}, 1.0, 1.0, 0, true, 1, 1, 2, 2.2, 300, false,
                          std::vector<ForceContainer<dim>>{}, false};

  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);

  int p0 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0,0, 0}, 0, m);
  int p1 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0,1, 0}, 0, m);
  int p2 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1,0, 0}, 0, m);
  int p3 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1,1, 0}, 0, m);
  int p4 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0, 0, 1}, 0, m);
  int p5 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0, 1, 1}, 0, m);
  int p6 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1, 0, 1}, 0, m);
  int p7 = Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1, 1, 1}, 0, m);

  EXPECT_EQ(p0, 0);
  EXPECT_EQ(p1, 1);
  EXPECT_EQ(p2, 2);
  EXPECT_EQ(p3, 3);
  EXPECT_EQ(p4, 4);
  EXPECT_EQ(p5, 5);
  EXPECT_EQ(p6, 6);
  EXPECT_EQ(p7, 7);
}

/**
 * Tests correctness of Linking in 2D.
 */
TEST(Membrane_Generator_2D_DirectSumContainer, linking){ // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0}, {2,2}, {0.0, 0.0}, 1.0, 1.0, 0, true, 1, 1, 2, 2.2, 300, false,
                          std::vector<ForceContainer<dim>>{}, false};

  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);

  auto p0 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0, 0}, 0, m));
  auto p1 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0, 1}, 0, m));
  auto p2 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1, 0}, 0, m));
  auto p3 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1, 1}, 0, m));

  std::vector<Particle<dim> *> neighbours{&p.getParticles()[p1], &p.getParticles()[p2]};
  std::vector<Particle<dim> *> diagNeighbours{&p.getParticles()[p3]};

  EXPECT_EQ(p.getParticles()[p0].getNeighbours(), neighbours);
  EXPECT_EQ(p.getParticles()[p0].getDiagonalNeighbours(), diagNeighbours);
}

/**
 * Tests correctness of Linking in 3D.
 */
TEST(Membrane_Generator_3D_DirectSumContainer, linking){  // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  MembraneArgument<dim> m{Vector<dim>{0.0, 0.0, 0.0}, {2, 2, 2}, {0.0, 0.0, 0.0}, 1.0, 1.0, 0, true, 1, 1, 2, 2.2, 300, false,
                          std::vector<ForceContainer<dim>>{}, false};

  DirectSumContainer<dim> p{};

  Generator<RectangularArgument<dim>, dim>::generate(m, p);

  auto p0 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0, 0, 0}, 0, m));
  auto p1 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0, 1, 0}, 0, m));
  auto p2 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1, 0, 0}, 0, m));
  auto p3 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1, 1, 0}, 0, m));
  auto p4 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0, 0, 1}, 0, m));
  auto p5 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({0, 1, 1}, 0, m));
  auto p6 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1, 0, 1}, 0, m));
  auto p7 =
      static_cast<unsigned long>(Generator<RectangularArgument<dim>, dim>::getPositionInContainer({1, 1, 1}, 0, m));

  std::vector<Particle<dim> *> neighbours{&p.getParticles()[p4], &p.getParticles()[p1], &p.getParticles()[p2]};
  std::vector<Particle<dim> *> diagNeighbours{&p.getParticles()[p5], &p.getParticles()[p6], &p.getParticles()[p3], &p.getParticles()[p7]};

  EXPECT_EQ(p.getParticles()[p0].getNeighbours(), neighbours);
  EXPECT_EQ(p.getParticles()[p0].getDiagonalNeighbours(), diagNeighbours);
}

//----------------------------------------Sphere----------------------------------------

/**
* Tests correctness of 2d generation for Spheres.
*/
TEST(SphereGenerator_2D_DirectSumContainer, generate) { // NOLINT(cert-err58-cpp)
  double distance = 1.1225;
  double mass = 1.0;
  constexpr int dim = 2;
  int rad = 2;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, rad, {0.0, 0.0}, distance, mass, 0.1, true, 1, 5, 2, true, {}};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);
  EXPECT_EQ(p.size(), 13);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&s, &rad](const Particle<dim> &p1) {
        return ArrayUtils::L2Norm(p1.getX() - s.getCenterCoordinates()) > rad + 0.01 * s.getDistance();
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), s.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), s.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), s.getDepthOfPotentialWell());
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

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, rad, {0.0, 0.0}, distance, mass, 0.1, false, 1, 5, 2, true, {}};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);
  EXPECT_EQ(p.size(), 8);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&s, &rad](const Particle<dim> &p1) {
        return (ArrayUtils::L2Norm(p1.getX() - s.getCenterCoordinates()) > rad + 0.01 * s.getDistance()
            || ArrayUtils::L2Norm(p1.getX() - s.getCenterCoordinates()) < rad + 0.6 * s.getDistance());
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), s.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), s.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), s.getDepthOfPotentialWell());
    }
  }
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

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0, 0.0}, rad, {0.0, 0.0, 0.0}, distance, mass, 0.1, true, 1, 5, 2, true, {}};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);
  EXPECT_EQ(p.size(), 33);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&s, &rad](const Particle<dim> &p1) {
        return ArrayUtils::L2Norm(p1.getX() - s.getCenterCoordinates()) > rad + 0.01 * s.getDistance();
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), s.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), s.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), s.getDepthOfPotentialWell());
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

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, rad, {0.0, 0.0}, distance, mass, 0.1, false, 1, 5, 2, true, {}};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);
  EXPECT_EQ(p.size(), 26);

  for (unsigned long i = 0; i < dim; i++) {
    for (auto j = 0; j < dim; j++) {
      ASSERT_TRUE(std::find_if(p.getParticles().begin(), p.getParticles().end(), [&s, &rad](const Particle<dim> &p1) {
        return (ArrayUtils::L2Norm(p1.getX() - s.getCenterCoordinates()) > rad + 0.01 * s.getDistance()
            || ArrayUtils::L2Norm(p1.getX() - s.getCenterCoordinates()) < rad + 0.6 * s.getDistance());
      }) != p.getParticles().end());
      EXPECT_EQ(p.getParticles()[i].getM(), mass);
      EXPECT_EQ(p.getParticles()[i].getType(), s.getType());
      EXPECT_EQ(p.getParticles()[i].getZeroCrossing(), s.getZeroCrossing());
      EXPECT_EQ(p.getParticles()[i].getPotentialWellDepth(), s.getDepthOfPotentialWell());
    }
  }
}

/**
* Tests correctness of 2d applyMotion for Spheres.
*/
TEST(SpheresGenerator_2D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, 1, {0.0, 0.0}, 1.0, 1.0, 0.1, true, 1, 5, 0, false, {}};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 2d applyMotion for Spheres.
*/
TEST(SpheresGenerator_2D_DirectSumContainer, applyNoMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0}, 1, {0.0, 0.0}, 1.0, 1.0, 0.0, true, 1, 5, 0, false, {}};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0}));
}

/**
* Tests correctness of 3d applyMotion for Spheres.
*/
TEST(SpheresGenerator_3D_DirectSumContainer, applyMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0, 0.0}, 1, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.1, true, 1, 5, 0, false, {}};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_FALSE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}

/**
* Tests correctness of 3d applyMotion for Spheres.
*/
TEST(SpheresGenerator_3D_DirectSumContainer, applyZeroMotion) { // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;

  SphereArgument<dim> s{Vector<dim>{0.0, 0.0, 0.0}, 1, {0.0, 0.0, 0.0}, 1.0, 1.0, 0.0, true, 1, 5, 0, false, {}};
  DirectSumContainer<dim> p{};

  Generator<SphereArgument<dim>, dim>::generate(s, p);

  EXPECT_TRUE(p.getParticles()[0].getV() == (Vector<dim>{0, 0, 0}));
}
