#include "FileReader.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

FileReader::FileReader() = default;

FileReader::~FileReader() = default;

void FileReader::readFile(ParticleContainer &particleContainer, const std::string &filename) {
  std::array<double, 3> x{};
  std::array<double, 3> v{};
  double m;
  int numParticles = 0;

  std::ifstream inputFile(filename);
  std::string tmpString;

  if (inputFile.is_open()) {

    getline(inputFile, tmpString);
    std::cout << "Read line: " << tmpString << std::endl;

    while (tmpString.empty() or tmpString[0] == '#') {
      getline(inputFile, tmpString);
      std::cout << "Read line: " << tmpString << std::endl;
    }

    std::istringstream numStream(tmpString);
    numStream >> numParticles;
    std::cout << "Reading " << numParticles << "." << std::endl;
    getline(inputFile, tmpString);
    std::cout << "Read line: " << tmpString << std::endl;

    for (int i = 0; i < numParticles; i++) {
      std::istringstream dataStream(tmpString);

      for (auto &xj: x) {
        dataStream >> xj;
      }
      for (auto &vj: v) {
        dataStream >> vj;
      }
      if (dataStream.eof()) {
        std::cout << "Error reading file: eof reached unexpectedly reading from line " << i << std::endl;
        exit(-1);
      }
      dataStream >> m;
      particleContainer.addParticle(Particle{Vector(x), Vector(v), m});

      getline(inputFile, tmpString);
      std::cout << "Read line: " << tmpString << std::endl;
    }
  } else {
    std::cout << "Error: could not open file " << filename << std::endl;
    exit(-1);
  }
}
