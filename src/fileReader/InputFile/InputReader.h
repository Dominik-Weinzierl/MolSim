#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>

#include "container/ParticleContainer.h"
#include "logger/Logger.h"
#include "physics/Vector/Vector.h"

/**
 * FileReader class reads a file and fills the provided ParticleContainer with Particle(s).
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class InputReader {
 private:

  //----------------------------------------Methods----------------------------------------

  /**
   * Read files based on the dimension and ignores the third value if simulation is 2D.
   * @param particleContainer container in which be store the Particle(s)
   * @param numParticles amount of particles
   * @param inputFile input file as stream
   */
  static void readParticles(ParticleContainer<dim> &particleContainer, int numParticles, std::ifstream &inputFile);
  // Since we expect only dim two or three, there is no default implementation required.

 public:
  /**
   * ReadFile Method adds the particles to the given particleContainer.
   * @param particleContainer container in which be store the Particle(s)
   * @param filename input filename
   */
  static void readFile(ParticleContainer<dim> &particleContainer, const std::string &filename) {
    std::ifstream inputFile(filename);
    std::string tmpString;

    if (inputFile.is_open()) {
      SPDLOG_INFO("Opened file {}", filename);
      int numParticles = 0;

      getline(inputFile, tmpString);

      while (tmpString.empty() or tmpString[0] == '#') {
        getline(inputFile, tmpString);
      }

      std::istringstream numStream(tmpString);
      numStream >> numParticles;

      readParticles(particleContainer, numParticles, inputFile);
    } else {
      SPDLOG_ERROR("Could not open file {}", filename);
      // spdlog is not always active -> this error should be visible even if spdlog is deactivated
      std::cerr << "Could not open file " << filename << std::endl;
      exit(-1);
    }
  }
};
