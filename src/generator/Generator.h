#pragma once

#include "particles/ParticleContainer.h"
#include "particles/Particle.h"
#include "utils/MaxwellBoltzmannDistribution.h"

struct GeneratorArguments {
};

template<typename T, size_t dim, typename std::enable_if<std::is_base_of<GeneratorArguments, T>::value,
                                                         bool>::type = true>
class Generator {
 public:
  static void generate(const T &g, ParticleContainer<dim> &container);

 private:
  static void applyMotion(double meanValue, Particle<dim> &p) {
    Vector<dim> t = p.getV();
    auto max = maxwellBoltzmannDistributedVelocity<dim>(meanValue);
    p.setV(t + max);
  }
};

