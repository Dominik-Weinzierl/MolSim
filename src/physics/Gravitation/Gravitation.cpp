#include "Gravitation.h"
#include <cmath>
#include <iostream>
#include <utils/ArrayUtils.h>
#include "physics/Vector/Vector.h"

void Gravitation::calculateF(ParticleContainer &particleContainer) const {
  //std::cout << "[GRAVITATION] Started calculating force" << std::endl;
  for (auto &p: particleContainer) {
    p.setOldF(p.getF());
    p.setF(Physics::ZERO);
  }
  for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
    for (auto j = i + 1; j != particleContainer.end(); ++j) {
      const auto difference = j->getX() - i->getX();
      Vector force = difference;
      const auto l2Norm = ArrayUtils::L2Norm(difference);
      force *= i->getM() * j->getM();
      force /= std::pow(l2Norm, 3);

      i->updateForce(force);
      j->updateForce(-force);
    }
  }
  //std::cout << "[GRAVITATION] Ended calculating force" << std::endl;;
}

void Gravitation::calculateV(ParticleContainer &particleContainer, const double deltaT) const {
  //std::cout << "[GRAVITATION] Started calculating velocity" << std::endl;;
  for (auto &p: particleContainer) {
    Vector velocity = (p.getOldF() + p.getF());
    velocity /= (2 * p.getM());
    velocity *= deltaT;
    velocity += p.getV();
    p.setV(velocity);
  }
  //std::cout << "[GRAVITATION] Ended calculating velocity" << std::endl;;
}
void Gravitation::calculateX(ParticleContainer &particleContainer, const double deltaT) const {
  //std::cout << "[GRAVITATION] Started calculating position" << std::endl;
  const auto deltaTPow = deltaT * deltaT;

  for (auto &p: particleContainer) {
    Vector position = p.getF();
    position /= 2 * p.getM();
    position *= deltaTPow;
    position += p.getX();
    position += deltaT * p.getV();

    p.setX(position);
  }
  //std::cout << "[GRAVITATION] Ended calculating position" << std::endl;;
}

void Gravitation::calculateNextStep(ParticleContainer &particleContainer, double deltaT) const {
  // calculate new x
  calculateX(particleContainer, deltaT);
  // calculate new f
  calculateF(particleContainer);
  // calculate new v
  calculateV(particleContainer, deltaT);
}
