#include "generator/GeneratorArguments/SphereArgument.h"
#include "generator/GeneratorArguments/variants/CuboidArgument.h"
#include "generator/GeneratorArguments/variants/MembraneArgument.h"
#include "generator/Generator.h"

template<>
void generateRectangular(const RectangularArgument<3> &t, ParticleContainer<3> &container){
  if (t.getPacked()) {
    for (auto x = 0; x < t.getDimensions()[0]; ++x) {
      for (auto y = 0; y < t.getDimensions()[1]; ++y) {
        for (auto z = 0; z < t.getDimensions()[2]; ++z) {
          Vector<3> pos
              {x * t.getDistance() + t.getStartingCoordinates()[0], y * t.getDistance() + t.getStartingCoordinates()[1],
               z * t.getDistance() + t.getStartingCoordinates()[2]};
          Particle<3> p
              {pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(), t.getType()};
          applyMotion(t.getMeanValue(), p);
          container.addParticle(p);
        }
      }
    }
  } else {
    std::array<int, 2> xMinMax{0, t.getDimensions()[0] - 1};
    std::array<int, 2> yMinMax{0, t.getDimensions()[1] - 1};
    std::array<int, 2> zMinMax{0, t.getDimensions()[2] - 1};

    for (auto x: xMinMax) {
      for (auto y = 0; y < t.getDimensions()[1]; ++y) {
        for (auto z = 0; z < t.getDimensions()[2]; ++z) {
          Vector<3> pos
              {x * t.getDistance() + t.getStartingCoordinates()[0], y * t.getDistance() + t.getStartingCoordinates()[1],
               z * t.getDistance() + t.getStartingCoordinates()[2]};
          Particle<3> p
              {pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(), t.getType()};
          Generator<T, 3>::applyMotion(t.getMeanValue(), p);
          container.addParticle(p);
        }
      }
    }

    for (auto y: yMinMax) {
      for (auto x = 1; x < t.getDimensions()[0] - 1; ++x) {
        for (auto z = 0; z < t.getDimensions()[2]; ++z) {
          Vector<3> pos
              {x * t.getDistance() + t.getStartingCoordinates()[0], y * t.getDistance() + t.getStartingCoordinates()[1],
               z * t.getDistance() + t.getStartingCoordinates()[2]};
          Particle<3> p
              {pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(), t.getType()};
          Generator<T, 3>::applyMotion(t.getMeanValue(), p);
          container.addParticle(p);
        }
      }
    }

    for (auto z: zMinMax) {
      for (auto x = 1; x < t.getDimensions()[0] - 1; ++x) {
        for (auto y = 1; y < t.getDimensions()[1] - 1; ++y) {
          Vector<3> pos
              {x * t.getDistance() + t.getStartingCoordinates()[0], y * t.getDistance() + t.getStartingCoordinates()[1],
               z * t.getDistance() + t.getStartingCoordinates()[2]};
          Particle<3> p
              {pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(), t.getType()};
          Generator<T, 3>::applyMotion(t.getMeanValue(), p);
          container.addParticle(p);
        }
      }
    }
  }
}

template<typename T, typename std::enable_if<std::is_base_of<RectangularArgument<2>, T>::value,
                                             bool>::type = true>
void generateRectangular(const RectangularArgument<2> &t, ParticleContainer<2> &container){
  if (t.getPacked()) {
    for (auto x = 0; x < t.getDimensions()[0]; ++x) {
      for (auto y = 0; y < t.getDimensions()[1]; ++y) {
        Vector<2> pos
            {x * t.getDistance() + t.getStartingCoordinates()[0], y * t.getDistance() + t.getStartingCoordinates()[1]};
        Particle<2>
            p{pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(), t.getType()};
        Generator<T, 2>::applyMotion(t.getMeanValue(), p);
        container.addParticle(p);
      }
    }
  } else {
    std::array<int, 2> xMinMax{0, t.getDimensions()[0] - 1};
    std::array<int, 2> yMinMax{0, t.getDimensions()[1] - 1};

    for (auto x: xMinMax) {
      for (int y = 0; y < t.getDimensions()[1]; ++y) {
        Vector<2> pos
            {x * t.getDistance() + t.getStartingCoordinates()[0], y * t.getDistance() + t.getStartingCoordinates()[1]};
        Particle<2>
            p{pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(), t.getType()};
        Generator<T, 2>::applyMotion(t.getMeanValue(), p);
        container.addParticle(p);
      }
    }

    for (auto y: yMinMax) {
      for (int x = 1; x < t.getDimensions()[0] - 1; ++x) {
        Vector<2> pos
            {x * t.getDistance() + t.getStartingCoordinates()[0], y * t.getDistance() + t.getStartingCoordinates()[1]};
        Particle<2>
            p{pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(), t.getType()};
        Generator<T, 2>::applyMotion(t.getMeanValue(), p);
        container.addParticle(p);
      }
    }
  }
}

template<>
void Generator<RectangularArgument<3>, 3>::generate(const RectangularArgument<3> &c, ParticleContainer<3> &container) {
  SPDLOG_TRACE("Cuboid generated!");
  generateRectangular(c, container);
}

template<>
void Generator<RectangularArgument<2>, 2>::generate(const RectangularArgument<2> &c, ParticleContainer<2> &container) {
  SPDLOG_TRACE("Cuboid generated!");
  generateRectangular(c, container);
}

template<>
void Generator<RectangularArgument<3>, 3>::generate(const RectangularArgument<3> &m, ParticleContainer<3> &container) {
  SPDLOG_TRACE("Membrane generated!");
  generateRectangular(m, container);
}

template<>
void Generator<RectangularArgument<2>, 2>::generate(const RectangularArgument<2> &m, ParticleContainer<2> &container) {
  SPDLOG_TRACE("Membrane generated!");
  generateRectangular(m, container);
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
