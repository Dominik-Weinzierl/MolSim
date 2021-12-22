#include <gtest/gtest.h>

#include "main/MolSim.h"
#include "fileReader/VTKReader/VTKReader.h"
#include "container/DirectSum/DirectSumContainer.h"
#include "particles/Particle.h"

/**
 * ***************************************************
 * Test correct functionality of the class VTKReader.
 * ******************************************+********
 */

/**
 * Tests the generation of two particles from the VTKReader.
 */
TEST(VTKReader_2D, simple_test) { // NOLINT(cert-err58-cpp)
  constexpr size_t dim = 2;

  DirectSumContainer<dim> d{};
  VTKReader<dim>::readFromFile(d, "../../tests/VTKReader/input/simple_test.vtu");

  DirectSumContainer<dim> d1{};
  //Simple test particles
  Particle<dim> p{{3.0, 3.0}, {-1.0, -1.0}, {0, 0}, {0, 0}, 1, 1.2, 1, 0};
  Particle<dim> p1{{1.0, 1.0}, {-1.0, -1.0}, {0, 0}, {0, 0}, 1, 1.2, 1, 0};
  d1.addParticle(p);
  d1.addParticle(p1);

  EXPECT_EQ(d.getParticles(), d1.getParticles());
}

/**
 * Tests the generation of two particles from a xml-source and a txt-source.
 */
TEST(VTKReader_2D, two_sources_test) { // NOLINT(cert-err58-cpp)
  constexpr size_t dim = 2;

  MolSim<dim> sim{};
  sim.setup({"-x", "-f", "../../tests/VTKReader/input/txt_test.xml"});

  DirectSumContainer<dim> d{};
  //Simple test particles
  Particle<dim> p{{3.0, 3.0}, {-1.0, -1.0}, {0, 0}, {0, 0}, 1, 1.2, 1, 0};
  Particle<dim> p1{{1.0, 1.0}, {-1.0, -1.0}, {0, 0}, {0, 0}, 1, 1.2, 1, 0};
  //TXT test particles
  Particle<dim> p2{{0.0, 0.0}, {0.0, 0.0}, 1.0};
  Particle<dim> p3{{2.0, 2.0}, {-1.0, -1.0}, 1.0};
  d.addParticle(p);
  d.addParticle(p1);
  d.addParticle(p2);
  d.addParticle(p3);

  EXPECT_EQ(sim.getParticleContainer()->getParticles(), d.getParticles());
}

/**
* Tests the generation of two particles from a xml-source and a cuboid of 4 particles.
*/
TEST(VTKReader_2D, generator_test) { // NOLINT(cert-err58-cpp)
  constexpr size_t dim = 2;

  MolSim<dim> sim{};
  sim.setup({"-x", "-f", "../../tests/VTKReader/input/generator_test.xml"});

  DirectSumContainer<dim> d{};
  //Simple test particles
  Particle<dim> p{{3.0, 3.0}, {-1.0, -1.0}, {0, 0}, {0, 0}, 1, 1.2, 1, 0};
  Particle<dim> p1{{1.0, 1.0}, {-1.0, -1.0}, {0, 0}, {0, 0}, 1, 1.2, 1, 0};
  //Cuboid
  Particle<dim> p2{{0.0, 0.0}, {0.0, 0.0}, {0, 0}, {0, 0}, 1, 1, 5, 0};
  Particle<dim> p3{{0.0, 1.0}, {0.0, 0.0}, {0, 0}, {0, 0}, 1, 1, 5, 0};
  Particle<dim> p4{{1.0, 0.0}, {0.0, 0.0}, {0, 0}, {0, 0}, 1, 1, 5, 0};
  Particle<dim> p5{{1.0, 1.0}, {0.0, 0.0}, {0, 0}, {0, 0}, 1, 1, 5, 0};
  d.addParticle(p);
  d.addParticle(p1);
  d.addParticle(p2);
  d.addParticle(p3);
  d.addParticle(p4);
  d.addParticle(p5);

  EXPECT_EQ(sim.getParticleContainer()->getParticles(), d.getParticles());
}

/**
 * Tests the generation of two particles from two xml-sources.
 */
TEST(VTKReader_3D, sources_test) { // NOLINT(cert-err58-cpp)
  constexpr size_t dim = 3;

  MolSim<dim> sim{};
  sim.setup({"-x", "-f", "../../tests/VTKReader/input/two_checkpoints_test.xml"});

  DirectSumContainer<dim> d{};
  //Simple test particles
  Particle<dim> p{{3.0, 3.0, 0}, {-1.0, -1.0, 0}, {0, 0, 0}, {0, 0, 0}, 1, 1.2, 1, 0};
  Particle<dim> p1{{1.0, 1.0, 0}, {-1.0, -1.0, 0}, {0, 0, 0}, {0, 0, 0}, 1, 1.2, 1, 0};
  //Two checkpoints test particles
  Particle<dim> p2{{4.0, 4.0, 0}, {-1.0, -1.0, 0}, {0, 0, 0}, {0, 0, 0}, 1, 1.2, 1, 0};
  Particle<dim> p3{{2.0, 2.0, 0}, {-1.0, -1.0, 0}, {0, 0, 0}, {0, 0, 0}, 1, 1.2, 1, 0};
  d.addParticle(p);
  d.addParticle(p1);
  d.addParticle(p2);
  d.addParticle(p3);

  EXPECT_EQ(sim.getParticleContainer()->getParticles(), d.getParticles());
}
