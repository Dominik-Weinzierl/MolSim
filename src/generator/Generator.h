#pragma once

#include <generator/GeneratorArguments/CuboidArgument.h>
#include "particles/ParticleContainer.h"
#include "particles/Particle.h"
#include "utils/MaxwellBoltzmannDistribution.h"

struct GeneratorArguments {
};

template<typename T, typename std::enable_if<std::is_base_of<GeneratorArguments, T>::value, bool>::type = true>
class Generator {
 public:
  static void generate(T &g, ParticleContainer &container);

 private:
  static void applyMotion(double meanValue, Particle &p) {
    Vector<> t = p.getV();
    auto max = maxwellBoltzmannDistributedVelocity(meanValue, 2);
    p.setV(t + max);
  }
};

