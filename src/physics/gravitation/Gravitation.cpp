#include "Gravitation.h"
#include <cmath>
#include <iostream>
#include <utils/ArrayUtils.h>
#include "physics/vector/Vector.h"

void Gravitation::calculateF(ParticleContainer &particleContainer) const {
  //std::cout << "[GRAVITATION] Started calculating force" << std::endl;
  const Vector zero;
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(zero);
  }
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i; ++j != particleContainer.end();) {
      auto difference = (j->getX() - i->getX());
      auto l2Norm = ArrayUtils::L2Norm(difference);
      auto pow = (std::pow((l2Norm), 3));
      auto factor = ((i->getM() * j->getM()) / pow);
      auto force = factor * difference;
      i->setF(i->getF() + force);
      j->setF(j->getF() - force);
    }
  }
  //std::cout << "[GRAVITATION] Ended calculating force" << std::endl;;
}

void Gravitation::calculateV(ParticleContainer &particleContainer, const double deltaT) const {
  //std::cout << "[GRAVITATION] Started calculating velocity" << std::endl;;
  for (auto &p: particleContainer) {
    auto &oldV = p.getV();
    auto &oldF = p.getOldF();
    auto &f = p.getF();
    const auto &m = p.getM();

    p.setV(oldV + deltaT * ((oldF + f) / (2 * m)));
  }
  //std::cout << "[GRAVITATION] Ended calculating velocity" << std::endl;;
}
void Gravitation::calculateX(ParticleContainer &particleContainer, const double deltaT) const {
  //std::cout << "[GRAVITATION] Started calculating position" << std::endl;
  for (auto &p: particleContainer) {
    auto &v = p.getV();
    auto &oldX = p.getX();
    auto &oldF = p.getOldF();
    const auto &m = p.getM();

    p.setX(oldX + deltaT * v + (deltaT * deltaT) * (oldF / (2 * m)));
  }
  //std::cout << "[GRAVITATION] Ended calculating position" << std::endl;;
}
