#include <generator/GeneratorArguments/SphereArgument.h>
#include "SphereGenerator.h"

void SphereGenerator::generate(GeneratorArguments &g, ParticleContainer &pc) {

  // Usage of static_cast since we know that we'll only operate on CuboidArguments
  auto &c = static_cast<SphereArgument &>(g); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
  double rad = c.radius * c.distance;
  std::array<double, 3>
      corner{c.centerCoordinates[0] - rad, c.centerCoordinates[1] - rad, c.centerCoordinates[2] - rad};
  for (auto x = 0; x <= 2 * c.radius; ++x) {
    for (auto y = 0; y <= 2 * c.radius; ++y) {
      for (auto z = 0; z <= 2 * c.radius; ++z) {
        Vector<> pos{x * c.distance + corner[0], y * c.distance + corner[1], z * c.distance + corner[2]};

        if (ArrayUtils::L2Norm(pos - c.centerCoordinates) > rad)
          continue;

        Particle p{pos, c.initialVelocity, c.mass};
        applyMotion(c.meanValue, p);
        pc.addParticle(p);
      }
    }
  }
}

void SphereGenerator::applyMotion(double meanValue, Particle &p) {
  Vector<> t = p.getV();
  auto max = maxwellBoltzmannDistributedVelocity(meanValue, 2);
  p.setV(t + max);
}
