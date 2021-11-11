#include "CuboidGenerator.h"
#include "generator/GeneratorArguments/CuboidArgument.h"

void CuboidGenerator::generate(GeneratorArguments &g, ParticleContainer &container) {

  // Usage of static_cast since we know that we'll only operate on CuboidArguments
  auto &c = static_cast<CuboidArgument &>(g); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)

  for (auto x = 0; x < c.dimensions[0]; ++x) {
    for (auto y = 0; y < c.dimensions[1]; ++y) {
      for (auto z = 0; z < c.dimensions[2]; ++z) {
        Vector pos{x * c.distance + c.startingCoordinates[0], y * c.distance + c.startingCoordinates[1],
                   z * c.distance + c.startingCoordinates[3]};
        Particle p{pos, c.initialVelocity, c.mass};
        applyMotion(c.meanValue, p);
        container.addParticle(p);
      }
    }
  }
}

//TODO: decide whether dimensions should be 3 or set to 3
void CuboidGenerator::applyMotion(double meanValue, Particle &p) {
  Vector t = p.getV();
  auto max = maxwellBoltzmannDistributedVelocity(meanValue, 2);
  p.setV(t + max);
}
