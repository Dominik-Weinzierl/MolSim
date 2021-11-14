#include "generator/GeneratorArguments/CuboidArgument.h"
#include "Generator.h"

template<>
void Generator<CuboidArgument>::generate(CuboidArgument &c, ParticleContainer &container) {
  for (auto x = 0; x < c.dimensions[0]; ++x) {
    for (auto y = 0; y < c.dimensions[1]; ++y) {
      for (auto z = 0; z < c.dimensions[2]; ++z) {
        Vector<> pos{x * c.distance + c.startingCoordinates[0], y * c.distance + c.startingCoordinates[1],
                     z * c.distance + c.startingCoordinates[3]};
        Particle p{pos, c.initialVelocity, c.mass};
        applyMotion(c.meanValue, p);
        container.addParticle(p);
      }
    }
  }
}

