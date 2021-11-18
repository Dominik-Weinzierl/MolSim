#include "Physics.h"

template<>
void Physics<3>::calculateV(ParticleContainer<3> &particleContainer, const double deltaT) {
  SPDLOG_DEBUG("started calculating velocities");
  for (auto &p: particleContainer) {
    SPDLOG_TRACE("Calculating velocity for {}", p.toString());
    double x;
    double y;
    double z;

    x = p.getV()[0] + deltaT * (p.getOldF()[0] + p.getF()[0]) / (2 * p.getM());
    y = p.getV()[1] + deltaT * (p.getOldF()[1] + p.getF()[1]) / (2 * p.getM());
    z = p.getV()[2] + deltaT * (p.getOldF()[2] + p.getF()[2]) / (2 * p.getM());

    p.setV(x, y, z);
  }
  SPDLOG_DEBUG("ended calculating velocities");
}

template<>
void Physics<2>::calculateV(ParticleContainer<2> &particleContainer, const double deltaT) {
  SPDLOG_DEBUG("started calculating velocities");
  for (auto &p: particleContainer) {
    SPDLOG_TRACE("Calculating velocity for {}", p.toString());
    double x;
    double y;

    x = p.getV()[0] + deltaT * (p.getOldF()[0] + p.getF()[0]) / (2 * p.getM());
    y = p.getV()[1] + deltaT * (p.getOldF()[1] + p.getF()[1]) / (2 * p.getM());

    p.setV(x, y);
  }
  SPDLOG_DEBUG("ended calculating velocities");
}

template<>
void Physics<3>::calculateX(ParticleContainer<3> &particleContainer, const double deltaT) {
  SPDLOG_DEBUG("started calculating positions");
  const auto deltaTPow = deltaT * deltaT;

  for (auto &p: particleContainer) {
    SPDLOG_TRACE("Calculating position for {}", p.toString());
    double x;
    double y;
    double z;

    x = p.getX()[0] + deltaT * p.getV()[0] + deltaTPow * (p.getF()[0] / (2 * p.getM()));
    y = p.getX()[1] + deltaT * p.getV()[1] + deltaTPow * (p.getF()[1] / (2 * p.getM()));
    z = p.getX()[2] + deltaT * p.getV()[2] + deltaTPow * (p.getF()[2] / (2 * p.getM()));

    p.setX(x, y, z);
  }
  SPDLOG_DEBUG("ended calculating positions");

}

template<>
void Physics<2>::calculateX(ParticleContainer<2> &particleContainer, const double deltaT) {
  SPDLOG_DEBUG("started calculating positions");
  const auto deltaTPow = deltaT * deltaT;

  for (auto &p: particleContainer) {
    SPDLOG_TRACE("Calculating position for {}", p.toString());
    double x;
    double y;

    x = p.getX()[0] + deltaT * p.getV()[0] + deltaTPow * (p.getF()[0] / (2 * p.getM()));
    y = p.getX()[1] + deltaT * p.getV()[1] + deltaTPow * (p.getF()[1] / (2 * p.getM()));

    p.setX(x, y);
  }
  SPDLOG_DEBUG("ended calculating positions");

}
