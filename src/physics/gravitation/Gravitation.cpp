#include "Gravitation.h"
#include "physics/Vector.h"
#include <cmath>
#include <iostream>

void Gravitation::calculateF(const ParticleContainer &particleContainer) const {
  std::cout << "[GRAVITATION] Started calculating force";
  const auto &pairs = particleContainer.getParticlePairs();
  for (const auto&[i, j]: pairs) {
    const auto difference = (j.getX() - i.getX());
    const auto factor = ((i.getM() * j.getM()) / (std::pow(Vector::euclideanNorm(i.getX(), j.getX()), 3)));
    auto force = factor * difference;
  }
  std::cout << "[GRAVITATION] Ended calculating force";
}

void Gravitation::calculateV(const ParticleContainer &particleContainer) const {
  std::cout << "[GRAVITATION] Started calculating velocity";
  std::cout << "[GRAVITATION] Ended calculating velocity";
}
void Gravitation::calculateX(const ParticleContainer &particleContainer) const {
  std::cout << "[GRAVITATION] Started calculating position";
  std::cout << "[GRAVITATION] Ended calculating position";
}
