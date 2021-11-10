#include "Physics.h"
#include "spdlog/spdlog.h"

void Physics::calculateV(ParticleContainer &particleContainer, const double deltaT) const {
  // SPDLOG_INFO("started calculating velocities");
  for (auto &p: particleContainer) {
    // SPDLOG_DEBUG("Calculating velocity for {}", p);
    Vector velocity = (p.getOldF() + p.getF());
    velocity /= (2 * p.getM());
    velocity *= deltaT;
    velocity += p.getV();
    p.setV(velocity);
  }
  // SPDLOG_INFO("ended calculating velocities");
}
void Physics::calculateX(ParticleContainer &particleContainer, const double deltaT) const {
  // SPDLOG_INFO("started calculating positions");
  const auto deltaTPow = deltaT * deltaT;

  for (auto &p: particleContainer) {
    // SPDLOG_DEBUG("Calculating position for {}", p);
    Vector position = p.getF();
    position /= 2 * p.getM();
    position *= deltaTPow;
    position += p.getX();
    position += deltaT * p.getV();

    p.setX(position);
  }
  // SPDLOG_INFO("ended calculating positions");

}

void Physics::calculateNextStep(ParticleContainer &particleContainer, double deltaT) const {
  // calculate new x
  calculateX(particleContainer, deltaT);
  // calculate new f
  calculateF(particleContainer);
  // calculate new v
  calculateV(particleContainer, deltaT);
}
