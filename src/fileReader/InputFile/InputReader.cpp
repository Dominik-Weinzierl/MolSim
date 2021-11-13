#include "InputReader.h"

#include "physics/Vector/Vector.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <spdlog/spdlog.h>

void InputReader::readFile(ParticleContainer &particleContainer, const std::string &filename) {
  std::ifstream inputFile(filename);
  std::string tmpString;

  if (inputFile.is_open()) {
    spdlog::info("Opened file {}", filename);
    double m;
    int numParticles = 0;
    Vector<> x;
    Vector<> v;

    getline(inputFile, tmpString);
    // std::cout << "Read line: " << tmpString << std::endl;

    while (tmpString.empty() or tmpString[0] == '#') {
      getline(inputFile, tmpString);
      // std::cout << "Read line: " << tmpString << std::endl;
    }

    std::istringstream numStream(tmpString);
    numStream >> numParticles;
    // std::cout << "Reading " << numParticles << "." << std::endl;
    getline(inputFile, tmpString);
    // std::cout << "Read line: " << tmpString << std::endl;

    for (int i = 0; i < numParticles; i++) {
      std::istringstream dataStream(tmpString);

      for (auto &xj: x) {
        dataStream >> xj;
      }
      for (auto &vj: v) {
        dataStream >> vj;
      }
      if (dataStream.eof()) {
        spdlog::error("Reached end of file {0} unexpectedly after {1} lines of data", filename, i);
        exit(-1);
      }
      dataStream >> m;
      particleContainer.addParticle({x, v, m});

      getline(inputFile, tmpString);
      // std::cout << "Read line: " << tmpString << std::endl;
    }
  } else {
    spdlog::error("Could not open file {}", filename);
    exit(-1);
  }
}
