#include "generator/GeneratorArguments/SphereArgument.h"
#include "generator/GeneratorArguments/CuboidArgument.h"
#include "Generator.h"

template<>
void Generator<CuboidArgument<3>, 3>::generate(const CuboidArgument<3> &c, ParticleContainer<3> &container) {
  SPDLOG_TRACE("Cuboid generated!");
  if (c.getPacked()) {
    for (auto x = 0; x < c.getDimensions()[0]; ++x) {
      for (auto y = 0; y < c.getDimensions()[1]; ++y) {
        for (auto z = 0; z < c.getDimensions()[2]; ++z) {
          Vector<3> pos
              {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1],
               z * c.getDistance() + c.getStartingCoordinates()[2]};
          Particle<3> p
              {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType()};
          applyMotion(c.getMeanValue(), p);
          container.addParticle(p);
        }
      }
    }
  } else {
    std::array<int, 2> xMinMax{0, c.getDimensions()[0] - 1};
    std::array<int, 2> yMinMax{0, c.getDimensions()[1] - 1};
    std::array<int, 2> zMinMax{0, c.getDimensions()[2] - 1};

    for (auto x: xMinMax) {
      for (auto y = 0; y < c.getDimensions()[1]; ++y) {
        for (auto z = 0; z < c.getDimensions()[2]; ++z) {
          Vector<3> pos
              {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1],
               z * c.getDistance() + c.getStartingCoordinates()[2]};
          Particle<3> p
              {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType()};
          applyMotion(c.getMeanValue(), p);
          container.addParticle(p);
        }
      }
    }

    for (auto y: yMinMax) {
      for (auto x = 1; x < c.getDimensions()[0] - 1; ++x) {
        for (auto z = 0; z < c.getDimensions()[2]; ++z) {
          Vector<3> pos
              {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1],
               z * c.getDistance() + c.getStartingCoordinates()[2]};
          Particle<3> p
              {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType()};
          applyMotion(c.getMeanValue(), p);
          container.addParticle(p);
        }
      }
    }

    for (auto z: zMinMax) {
      for (auto x = 1; x < c.getDimensions()[0] - 1; ++x) {
        for (auto y = 1; y < c.getDimensions()[1] - 1; ++y) {
          Vector<3> pos
              {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1],
               z * c.getDistance() + c.getStartingCoordinates()[2]};
          Particle<3> p
              {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType()};
          applyMotion(c.getMeanValue(), p);
          container.addParticle(p);
        }
      }
    }
  }
}

template<>
void Generator<CuboidArgument<2>, 2>::generate(const CuboidArgument<2> &c, ParticleContainer<2> &container) {
  SPDLOG_TRACE("Cuboid generated!");
  if (c.getPacked()) {
    for (auto x = 0; x < c.getDimensions()[0]; ++x) {
      for (auto y = 0; y < c.getDimensions()[1]; ++y) {
        Vector<2> pos
            {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1]};
        Particle<2>
            p{pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType()};
        applyMotion(c.getMeanValue(), p);
        container.addParticle(p);
      }
    }
  } else {
    std::array<int, 2> xMinMax{0, c.getDimensions()[0] - 1};
    std::array<int, 2> yMinMax{0, c.getDimensions()[1] - 1};

    for (auto x: xMinMax) {
      for (int y = 0; y < c.getDimensions()[1]; ++y) {
        Vector<2> pos
            {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1]};
        Particle<2>
            p{pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType()};
        applyMotion(c.getMeanValue(), p);
        container.addParticle(p);
      }
    }

    for (auto y: yMinMax) {
      for (int x = 1; x < c.getDimensions()[0] - 1; ++x) {
        Vector<2> pos
            {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1]};
        Particle<2>
            p{pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType()};
        applyMotion(c.getMeanValue(), p);
        container.addParticle(p);
      }
    }
  }
}

template<>
void Generator<SphereArgument<3>, 3>::generate(const SphereArgument<3> &c, ParticleContainer<3> &container) {
  SPDLOG_TRACE("Sphere generated!");
  double rad = c.getRadius() * c.getDistance();
  std::array<double, 3>
      corner{c.getCenterCoordinates()[0] - rad, c.getCenterCoordinates()[1] - rad, c.getCenterCoordinates()[2] - rad};
  for (auto x = 0; x <= 2 * c.getRadius(); ++x) {
    for (auto y = 0; y <= 2 * c.getRadius(); ++y) {
      for (auto z = 0; z <= 2 * c.getRadius(); ++z) {
        Vector<3>
            pos{x * c.getDistance() + corner[0], y * c.getDistance() + corner[1], z * c.getDistance() + corner[2]};

        // 0.01 * dist so that we don't have too many problems with the (in-)precision of floating point math, -0.6 to get a reasonable amount of particles to all sides if we don't want a filled sphere
        if (ArrayUtils::L2Norm(pos - c.getCenterCoordinates()) > rad + 0.01 * c.getDistance()
            || (!c.getPacked() && ArrayUtils::L2Norm(pos - c.getCenterCoordinates()) < rad - 0.6 * c.getDistance()))
          continue;

        Particle<3>
            p{pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType()};
        applyMotion(c.getMeanValue(), p);
        container.addParticle(p);
      }
    }
  }
}

template<>
void Generator<SphereArgument<2>, 2>::generate(const SphereArgument<2> &c, ParticleContainer<2> &container) {
  SPDLOG_TRACE("Sphere generated!");
  double rad = c.getRadius() * c.getDistance();
  std::array<double, 2> corner{c.getCenterCoordinates()[0] - rad, c.getCenterCoordinates()[1] - rad};
  for (auto x = 0; x <= 2 * c.getRadius(); ++x) {
    for (auto y = 0; y <= 2 * c.getRadius(); ++y) {
      Vector<2> pos{x * c.getDistance() + corner[0], y * c.getDistance() + corner[1]};

      // 0.01 * dist so that we don't have too many problems with the (in-)precision of floating point math, -0.6 to get a reasonable amount of particles to all sides if we don't want a filled sphere
      if (ArrayUtils::L2Norm(pos - c.getCenterCoordinates()) > rad + 0.01 * c.getDistance()
          || (!c.getPacked() && ArrayUtils::L2Norm(pos - c.getCenterCoordinates()) < rad - 0.6 * c.getDistance()))
        continue;

      Particle<2>
          p{pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType()};
      applyMotion(c.getMeanValue(), p);
      container.addParticle(p);
    }
  }
}
