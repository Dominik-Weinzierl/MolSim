#include "Gravitation.h"
#include "physics/vector/Vector.h"
#include <cmath>
#include <iostream>

void Gravitation::calculateF(ParticleContainer &particleContainer) const {
  std::cout << "[GRAVITATION] Started calculating force" << std::endl;
  auto &particles = particleContainer.getParticles();
  const Vector zero = Vector(0, 0, 0);
  for (auto &p: particles) {
    p.setOldF(p.getF());
    p.setF(zero);
  }
  auto &pairs = particleContainer.getParticlePairs();
  for (auto&[i, j]: pairs) {
    const auto &difference = (j.getX() - i.getX());
    const auto &factor = ((i.getM() * j.getM()) / (std::pow(Vector::euclideanNorm(i.getX(), j.getX()), 3)));
    const auto &force = factor * difference;
    i.setF(i.getF() + force);
    j.setF(i.getF() - force);
  }
  std::cout << "[GRAVITATION] Ended calculating force" << std::endl;;
}

void Gravitation::calculateV(ParticleContainer &particleContainer, const double deltaT) const {
  std::cout << "[GRAVITATION] Started calculating velocity" << std::endl;;
  auto &particles = particleContainer.getParticles();
  for (auto &p: particles) {
    const auto &oldV = p.getV();
    const auto &oldF = p.getOldF();
    const auto &f = p.getF();
    const auto &m = p.getM();

    p.setV(oldV + deltaT * (oldF + f) * (1 / (2 * m)));
  }
  std::cout << "[GRAVITATION] Ended calculating velocity" << std::endl;;
}
void Gravitation::calculateX(ParticleContainer &particleContainer, const double deltaT) const {
  std::cout << "[GRAVITATION] Started calculating position" << std::endl;
  auto &particles = particleContainer.getParticles();
  for (auto &p: particles) {
    const auto &v = p.getV();
    const auto &oldX = p.getX();
    const auto &f = p.getF();
    const auto &m = p.getM();

    p.setX(oldX + deltaT * v + (deltaT * deltaT) * (1 / (2 * m)) * f);
  }
  std::cout << "[GRAVITATION] Ended calculating position" << std::endl;;
}
