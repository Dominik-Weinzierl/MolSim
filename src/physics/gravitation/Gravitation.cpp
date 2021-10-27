#include "Gravitation.h"
#include "physics/Vector.h"
#include <cmath>

void Gravitation::calculateF(const ParticleContainer &particleContainer) {

  auto pairs = particleContainer.getParticlePairs();

  for (const auto&[i, j]: pairs) {
    // TODO: google const common practice
    auto force = (i.getM() * j.getM() / std::pow(Vector::euclideanNorm(i.getX(), j.getX()), 3)) * (j.getX() - i.getX());
  }
}
void Gravitation::calculateV(const ParticleContainer &particleContainer) {

}
void Gravitation::calculateX(const ParticleContainer &particleContainer) {

}
