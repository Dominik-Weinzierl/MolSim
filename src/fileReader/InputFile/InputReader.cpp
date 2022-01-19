#include "InputReader.h"

template<>
void InputReader<3>::readParticles(ParticleContainer<3> &particleContainer, int numParticles,
                                   std::ifstream &inputFile) {
  Vector<3> x;
  Vector<3> v;
  double m;
  std::string tmpString;
  getline(inputFile, tmpString);
  for (int i = 0; i < numParticles; i++) {
    std::istringstream dataStream(tmpString);

    for (auto &xj: x) {
      dataStream >> xj;
    }
    for (auto &vj: v) {
      dataStream >> vj;
    }
    if (dataStream.eof()) {
      SPDLOG_ERROR("Reached end of file unexpectedly after {} lines of data", i);
      exit(-1);
    }
    dataStream >> m;
    particleContainer.addParticle({x, v, m});

    getline(inputFile, tmpString);
  }
}

template<>
void InputReader<2>::readParticles(ParticleContainer<2> &particleContainer, int numParticles,
                                   std::ifstream &inputFile) {
  Vector<2> x;
  Vector<2> v;
  double dummy;
  double m;
  std::string tmpString;
  getline(inputFile, tmpString);
  for (int i = 0; i < numParticles; i++) {
    std::istringstream dataStream(tmpString);

    for (auto &xj: x) {
      dataStream >> xj;
    }
    dataStream >> dummy;
    for (auto &vj: v) {
      dataStream >> vj;
    }
    dataStream >> dummy;
    if (dataStream.eof()) {
      SPDLOG_ERROR("Reached end of file unexpectedly after {} lines of data", i);
      exit(-1);
    }
    dataStream >> m;
    particleContainer.addParticle({x, v, m});

    getline(inputFile, tmpString);
  }
}
