#include "generator/GeneratorArguments/SphereArgument.h"
#include "generator/GeneratorArguments/CuboidArgument.h"
#include "Generator.h"

template<>
void Generator<CuboidArgument<3>, 3>::generate(const CuboidArgument<3> &c, ParticleContainer<3> &container) {
  for (auto x = 0; x < c.dimensions[0]; ++x) {
    for (auto y = 0; y < c.dimensions[1]; ++y) {
      for (auto z = 0; z < c.dimensions[2]; ++z) {
        Vector<3> pos{x * c.distance + c.startingCoordinates[0], y * c.distance + c.startingCoordinates[1],
                      z * c.distance + c.startingCoordinates[3]};
        Particle<3> p{pos, c.initialVelocity, c.mass};
        applyMotion(c.meanValue, p);
        container.addParticle(p);
      }
    }
  }
}

template<>
void Generator<CuboidArgument<2>, 2>::generate(const CuboidArgument<2> &c, ParticleContainer<2> &container) {
  for (auto x = 0; x < c.dimensions[0]; ++x) {
    for (auto y = 0; y < c.dimensions[1]; ++y) {
      Vector<2> pos{x * c.distance + c.startingCoordinates[0], y * c.distance + c.startingCoordinates[1]};
      Particle<2> p{pos, c.initialVelocity, c.mass};
      applyMotion(c.meanValue, p);
      container.addParticle(p);
    }
  }
}

template<>
void Generator<SphereArgument<3>, 3>::generate(const SphereArgument<3> &c, ParticleContainer<3> &container) {
  double rad = c.radius * c.distance;
  std::array<double, 3>
      corner{c.centerCoordinates[0] - rad, c.centerCoordinates[1] - rad, c.centerCoordinates[2] - rad};
  for (auto x = 0; x <= 2 * c.radius; ++x) {
    for (auto y = 0; y <= 2 * c.radius; ++y) {
      for (auto z = 0; z <= 2 * c.radius; ++z) {
        Vector<3> pos{x * c.distance + corner[0], y * c.distance + corner[1], z * c.distance + corner[2]};

        if (ArrayUtils::L2Norm(pos - c.centerCoordinates) > rad)
          continue;

        Particle<3> p{pos, c.initialVelocity, c.mass};
        applyMotion(c.meanValue, p);
        container.addParticle(p);
      }
    }
  }
}

template<>
void Generator<SphereArgument<2>, 2>::generate(const SphereArgument<2> &c, ParticleContainer<2> &container) {
  double rad = c.radius * c.distance;
  std::array<double, 2> corner{c.centerCoordinates[0] - rad, c.centerCoordinates[1] - rad};
  for (auto x = 0; x <= 2 * c.radius; ++x) {
    for (auto y = 0; y <= 2 * c.radius; ++y) {
      Vector<2> pos{x * c.distance + corner[0], y * c.distance + corner[1]};

      if (ArrayUtils::L2Norm(pos - c.centerCoordinates) > rad)
        continue;

      Particle<2> p{pos, c.initialVelocity, c.mass};
      applyMotion(c.meanValue, p);
      container.addParticle(p);
    }
  }
}


