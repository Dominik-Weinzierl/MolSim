#include <gtest/gtest.h>

#include "physics/variants/HarmonicPotential.h"
#include "particles/Particle.h"

/**
 * ***************************************************
 * Test correct functionality of the class HarmonicPotential.
 * ******************************************+********
 */

/**
 * Test correct calculation of the calculateForceBetweenTwoParticles-Method 2D.
 */
TEST(Harmonic_Potential_2D, calculateForceBetweenTwoParticles){ // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;
  double l2Norm = 1;

  Particle<dim> i{{1, 0}, {0, 0}, 1, 0};
  Particle<dim> j{{0, 0}, {0, 0}, 1, 0};

  i.setParticleTypeToMolecule();
  j.setParticleTypeToMolecule();
  i.setMembraneArguments(10, 1.0);
  j.setMembraneArguments(0, 0);

  // k * (l2Norm - r0) * (xj - xi)/l2Norm => 10 * (1 - 1) * (-1)/1 = 10 * 0 * -1 = 0
  Vector<dim> calculated{0,0};
  EXPECT_EQ(HarmonicPotential::calculateForceBetweenTwoParticles(&i, &j, l2Norm), calculated);
}

/**
 * Test correct calculation of the calculateForceBetweenTwoParticles-Method 3D.
 */
TEST(Harmonic_Potential_3D, calculateForceBetweenTwoParticles){ // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;
  double l2Norm = 1;

  Particle<dim> i{{1, 0, 0}, {0, 0, 0}, 1, 0};
  Particle<dim> j{{0, 0, 0}, {0, 0, 0}, 1, 0};

  i.setParticleTypeToMolecule();
  j.setParticleTypeToMolecule();
  i.setMembraneArguments(10, 1.0);
  j.setMembraneArguments(0, 0);

  // k * (l2Norm - r0) * (xj - xi)/l2Norm => 10 * (1 - 1) * (-1)/1 = 10 * 0 * -1 = 0
  Vector<dim> calculated{0,0, 0};
  EXPECT_EQ(HarmonicPotential::calculateForceBetweenTwoParticles(&i, &j, l2Norm), calculated);
}

/**
 * Test correct calculation of the calculateForceBetweenTwoDiagonalParticles-Method 2D.
 */
TEST(Harmonic_Potential_2D, calculateForceBetweenTwoDiagonalParticles){ // NOLINT(cert-err58-cpp)
  constexpr int dim = 2;
  double l2Norm = 1;

  Particle<dim> i{{1, 0}, {0, 0}, 1, 0};
  Particle<dim> j{{0, 0}, {0, 0}, 1, 0};

  i.setParticleTypeToMolecule();
  j.setParticleTypeToMolecule();
  i.setMembraneArguments(10, -sqrt(2));
  j.setMembraneArguments(0, 0);

  // k * (l2Norm - r0) * (xj - xi)/l2Norm => 10 * (1 + 2) * (-1)/1 = 10 * 1 + 3 * -1 = -30
  Vector<dim> calculated{-30,0};
  EXPECT_NEAR(HarmonicPotential::calculateForceBetweenTwoDiagonalParticles(&i, &j, l2Norm)[0], calculated[0], 0.01);
}

/**
 * Test correct calculation of the calculateForceBetweenTwoDiagonalParticles-Method 3D.
 */
TEST(Harmonic_Potential_3D, calculateForceBetweenTwoDiagonalParticles){ // NOLINT(cert-err58-cpp)
  constexpr int dim = 3;
  double l2Norm = 1;

  Particle<dim> i{{1, 0, 0}, {0, 0, 0}, 1, 0};
  Particle<dim> j{{0, 0, 0}, {0, 0, 0}, 1, 0};

  i.setParticleTypeToMolecule();
  j.setParticleTypeToMolecule();
  i.setMembraneArguments(10, -std::sqrt(2));
  j.setMembraneArguments(0, 0);

  // k * (l2Norm - r0) * (xj - xi)/l2Norm => 10 * (1 - (-2)) * (-1)/1 = 10 * 3 * -1 = -30
  Vector<dim> calculated{-30,0, 0};
  EXPECT_NEAR(HarmonicPotential::calculateForceBetweenTwoDiagonalParticles(&i, &j, l2Norm)[0], calculated[0], 0.01);
}