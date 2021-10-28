#include "Gravitation.h"
#include "physics/vector/Vector.h"
#include <cmath>
#include <iostream>

void Gravitation::calculateF(const ParticleContainer &particleContainer) const {
  std::cout << "[GRAVITATION] Started calculating force";
  const auto &pairs = particleContainer.getParticlePairs();
  for (const auto&[i, j]: pairs) {
    const auto& difference = (j.getX() - i.getX());
    const auto& factor = ((i.getM() * j.getM()) / (std::pow(Vector::euclideanNorm(i.getX(), j.getX()), 3)));
    const auto& force = factor * difference;
  }
  std::cout << "[GRAVITATION] Ended calculating force";
}

void Gravitation::calculateV(const ParticleContainer &particleContainer, const double deltaT) const {
  std::cout << "[GRAVITATION] Started calculating velocity";
  const auto &particles = particleContainer.getParticles();
  for (const auto &p: particles) {
    const auto &oldV = p.getV();
    const auto &oldF = p.getOldF();
    const auto &f = p.getF();
    const auto &m = p.getM();

    Vector v = oldV + deltaT * (oldF + f) * (1 / (2 * m));
  }
  std::cout << "[GRAVITATION] Ended calculating velocity";
}
void Gravitation::calculateX(const ParticleContainer &particleContainer, const double deltaT) const {
  std::cout << "[GRAVITATION] Started calculating position";
  const auto &particles = particleContainer.getParticles();
  for (const auto &p: particles) {
    const auto &v = p.getV();
    const auto &oldX = p.getX();
    const auto &f = p.getF();
    const auto &m = p.getM();

    Vector x = oldX + deltaT * v + (deltaT * deltaT) * (1 / (2 * m)) * f;
  }
  std::cout << "[GRAVITATION] Ended calculating position";
}
