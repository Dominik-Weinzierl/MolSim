#include "Physics.h"
#include "spdlog/spdlog.h"

void Physics::calculateV(ParticleContainer &particleContainer, const double deltaT) {
  // SPDLOG_INFO("started calculating velocities");
  for (auto &p: particleContainer) {
    // SPDLOG_DEBUG("Calculating velocity for {}", p);
    double x = 0;
    double y = 0;
    double z = 0;

    x = p.getV()[0] + deltaT * (p.getOldF()[0] + p.getF()[0]) / (2 * p.getM());
    y = p.getV()[1] + deltaT * (p.getOldF()[1] + p.getF()[1]) / (2 * p.getM());
    z = p.getV()[2] + deltaT * (p.getOldF()[2] + p.getF()[2]) / (2 * p.getM());

    p.setV(x, y, z);
  }
  // SPDLOG_INFO("ended calculating velocities");
}
void Physics::calculateX(ParticleContainer &particleContainer, const double deltaT) {
  // SPDLOG_INFO("started calculating positions");
  const auto deltaTPow = deltaT * deltaT;

  for (auto &p: particleContainer) {
    // SPDLOG_DEBUG("Calculating position for {}", p);
    double x = 0;
    double y = 0;
    double z = 0;

    x = p.getX()[0] + deltaT * p.getV()[0] + deltaTPow * (p.getF()[0] / (2 * p.getM()));
    y = p.getX()[1] + deltaT * p.getV()[1] + deltaTPow * (p.getF()[1] / (2 * p.getM()));
    z = p.getX()[2] + deltaT * p.getV()[2] + deltaTPow * (p.getF()[2] / (2 * p.getM()));

    p.setX(x, y, z);
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
