#include "thermostat/FlowThermostat.h"

template<>
void FlowThermostat<3>::applyScaling(ParticleContainer<3> &c, double beta) {
  for (auto &p: c) {
    Vector<3> v = p.getV();
    v[0] *= beta;
    v[2] *= beta;
    p.setV(v);
  }
}

template<>
void FlowThermostat<2>::applyScaling(ParticleContainer<2> &c, double beta) {
  for (auto &p: c) {
    Vector<2> v = p.getV();
    v[0] *= beta;

    p.setV(v);
  }
}

