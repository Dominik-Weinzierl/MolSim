#include "Gravitation.h"
#include <cmath>
#include <iostream>
#include <utils/ArrayUtils.h>
#include "physics/Vector/Vector.h"

void Gravitation::calculateF(ParticleContainer &particleContainer) const {
  //std::cout << "[GRAVITATION] Started calculating force" << std::endl;
  const Vector zero;
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(zero);
  }
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i; ++j != particleContainer.end();) {
      const auto l2Norm = ArrayUtils::L2Norm(i->getX() - j->getX());
      const auto force = ((i->getM() * j->getM()) / std::pow(l2Norm, 3.0)) * (j->getX() - i->getX());

      i->setF(i->getF() + force);
      j->setF(j->getF() - force);
    }
  }
  //std::cout << "[GRAVITATION] Ended calculating force" << std::endl;;
}

void Gravitation::calculateV(ParticleContainer &particleContainer, const double deltaT) const {
  //std::cout << "[GRAVITATION] Started calculating velocity" << std::endl;;
  for (auto &p: particleContainer) {
    const auto &oldV = p.getV();
    const auto &oldF = p.getOldF();
    const auto &f = p.getF();
    const auto &m = p.getM();

    p.setV(oldV + deltaT * ((oldF + f) / (2 * m)));
  }
  //std::cout << "[GRAVITATION] Ended calculating velocity" << std::endl;;
}
void Gravitation::calculateX(ParticleContainer &particleContainer, const double deltaT) const {
  //std::cout << "[GRAVITATION] Started calculating position" << std::endl;
  for (auto &p: particleContainer) {
    const auto &v = p.getV();
    const auto &oldX = p.getX();
    const auto &oldF = p.getOldF();
    const auto &m = p.getM();

    p.setX(oldX + deltaT * v + (deltaT * deltaT) * (oldF / (2 * m)));
  }
  //std::cout << "[GRAVITATION] Ended calculating position" << std::endl;;
}
