#include "generator/GeneratorArguments/SphereArgument.h"
#include "generator/GeneratorArguments/variants/MembraneArgument.h"
#include "generator/Generator.h"

template<>
int Generator<RectangularArgument<2>, 2>::getPositionInContainer(std::array<int, 2> index, int zero,
                                                                 const RectangularArgument<2> &c) {
  int pos;
  if (c.getPacked()) {
    pos = zero + index[0] * c.getDimensions()[1] + index[1];
  } else {
    if (index[0] == 0) {
      pos = zero + index[1];
    } else if (index[0] == c.getDimensions()[0] - 1) {
      pos = zero + c.getDimensions()[1] + index[1];
    } else if (index[1] == 0) {
      pos = zero + 2 * c.getDimensions()[1] + index[0] - 1;
    } else if (index[1] == c.getDimensions()[1] - 1) {
      pos = zero + 2 * c.getDimensions()[1] + (c.getDimensions()[0] - 2) + index[0] - 1;
    } else {
      return -1;
    }
  }
  return pos;
}

template<>
int Generator<RectangularArgument<3>, 3>::getPositionInContainer(std::array<int, 3> index, int zero,
                                                                 const RectangularArgument<3> &c) {
  int pos;
  if (c.getPacked()) {
    // pos = z * area + x * column + y
    pos = zero + (index[2] * c.getDimensions()[0] * c.getDimensions()[1]) + index[0] * c.getDimensions()[1] + index[1];
  } else {
    if (index[0] == 0) {
      // pos = y * row + z
      pos = zero + index[1] * c.getDimensions()[0] + index[2];
    } else if (index[0] == c.getDimensions()[0] - 1) {
      // pos = area + y * row + z
      pos = zero + (c.getDimensions()[1] * c.getDimensions()[2]) + index[1] * c.getDimensions()[0] + index[2];
    } else if (index[1] == 0) {
      // 2 * area (left and right) + z * (dim(x) - 2) + x
      pos = zero + 2 * (c.getDimensions()[1] * c.getDimensions()[2]) + index[2] * (c.getDimensions()[0] - 2) + index[0]
          - 1;
    } else if (index[1] == c.getDimensions()[1] - 1) {
      // 2 * area (left and right) + dim(z) * (dim(x) -2) + z * (dim(x) - 2) + x
      pos =
          zero + 2 * (c.getDimensions()[1] * c.getDimensions()[2]) + (c.getDimensions()[2] * (c.getDimensions()[0] - 2))
              + index[2] * (c.getDimensions()[0] - 2) + index[0] - 1;
    } else if (index[2] == 0) {
      // 2 * area (left and right) + 2 * area (top and bottom) + (dim(x) - 2) * y + (x - 1)
      pos = zero + 2 * (c.getDimensions()[1] * c.getDimensions()[2])
          + 2 * (c.getDimensions()[2] * (c.getDimensions()[0] - 2)) + (c.getDimensions()[0] - 2) * index[1] + index[0]
          - 1;
    } else if (index[2] == c.getDimensions()[2] - 1) {
      // 2 * area (left and right) + 2 * area (top and bottom) + ((dim(x) - 2) * (dim(y) - 2)) + (dim(x) - 2) * y + (x - 1)
      pos = zero + 2 * (c.getDimensions()[1] * c.getDimensions()[2])
          + 2 * (c.getDimensions()[2] * (c.getDimensions()[0] - 2))
          + ((c.getDimensions()[0] - 2) * (c.getDimensions()[1] - 2)) + (c.getDimensions()[0] - 2) * index[1] + index[0]
          - 1;
    } else {
      return -1;
    }
  }
  return pos;
}

template<>
void Generator<RectangularArgument<2>, 2>::fixOutline(int zero, const MembraneArgument<2> &m,
                                                      ParticleContainer<2> &container) {

  std::array<int, 2> xMinMax{0, m.getDimensions()[0] - 1};
  std::array<int, 2> yMinMax{0, m.getDimensions()[1] - 1};

  for (auto x: xMinMax) {
    for (int y = 0; y < m.getDimensions()[1]; ++y) {
      setFixed(getPositionInContainer({x, y}, zero, m), container);
    }
  }

  for (auto y: yMinMax) {
    for (int x = 1; x < m.getDimensions()[0] - 1; ++x) {
      setFixed(getPositionInContainer({x, y}, zero, m), container);
    }
  }
}

template<>
void Generator<RectangularArgument<3>, 3>::fixOutline(int zero, const MembraneArgument<3> &m,
                                                      ParticleContainer<3> &container) {

  std::array<int, 2> xMinMax{0, m.getDimensions()[0] - 1};
  std::array<int, 2> yMinMax{0, m.getDimensions()[1] - 1};
  std::array<int, 2> zMinMax{0, m.getDimensions()[2] - 1};

  for (auto x: xMinMax) {
    for (auto y = 0; y < m.getDimensions()[1]; ++y) {
      for (auto z = 0; z < m.getDimensions()[2]; ++z) {
        setFixed(getPositionInContainer({x, y, z}, zero, m), container);
      }
    }
  }

  for (auto y: yMinMax) {
    for (auto x = 1; x < m.getDimensions()[0] - 1; ++x) {
      for (auto z = 0; z < m.getDimensions()[2]; ++z) {
        setFixed(getPositionInContainer({x, y, z}, zero, m), container);
      }
    }
  }

  if (m.getDimensions()[2] > 1) {
    for (auto z: zMinMax) {
      for (auto x = 1; x < m.getDimensions()[0] - 1; ++x) {
        for (auto y = 1; y < m.getDimensions()[1] - 1; ++y) {
          setFixed(getPositionInContainer({x, y, z}, zero, m), container);
        }
      }
    }
  }
}

template<>
void Generator<RectangularArgument<3>, 3>::generateRectangular(const RectangularArgument<3> &c,
                                                               ParticleContainer<3> &container) {

  int amount = static_cast<int>(container.size());
  if (c.getPacked()) {
    for (auto x = 0; x < c.getDimensions()[0]; ++x) {
      for (auto y = 0; y < c.getDimensions()[1]; ++y) {
        for (auto z = 0; z < c.getDimensions()[2]; ++z) {
          Vector<3> pos
              {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1],
               z * c.getDistance() + c.getStartingCoordinates()[2]};
          Particle<3> p
              {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType(),
               c.isFixed()};
          linkForce(p, c.getForces(), std::array<int, 3>{x, y, z});
          applyMotion(c.getMeanValue(), p);

          if (auto *m = dynamic_cast<const MembraneArgument<3> *>(&c)) {
            p.setParticleTypeToMolecule();
            p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());
          }

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
              {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType(),
               c.isFixed()};
          linkForce(p, c.getForces(), std::array<int, 3>{x, y, z});
          applyMotion(c.getMeanValue(), p);

          if (auto *m = dynamic_cast<const MembraneArgument<3> *>(&c)) {
            p.setParticleTypeToMolecule();
            p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());
          }

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
              {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType(),
               c.isFixed()};
          linkForce(p, c.getForces(), std::array<int, 3>{x, y, z});
          applyMotion(c.getMeanValue(), p);

          if (auto *m = dynamic_cast<const MembraneArgument<3> *>(&c)) {
            p.setParticleTypeToMolecule();
            p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());
          }

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
              {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType(),
               c.isFixed()};
          linkForce(p, c.getForces(), std::array<int, 3>{x, y, z});
          applyMotion(c.getMeanValue(), p);

          if (auto *m = dynamic_cast<const MembraneArgument<3> *>(&c)) {
            p.setParticleTypeToMolecule();
            p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());
          }

          container.addParticle(p);
        }
      }
    }
  }

  if (auto *m = dynamic_cast<const MembraneArgument<3> *>(&c)) {
    // Insert Particle pointer into vector
    for (auto i = static_cast<size_t>(amount); i < container.size(); ++i) {
      container.addMolecule(&container.getParticles()[i]);
    }

    // Fixed outline
    if (m->getFixedOutline()) {
      fixOutline(amount, *m, container);
    }

    for (auto x = 0; x < c.getDimensions()[0]; ++x) {
      for (auto y = 0; y < c.getDimensions()[1]; ++y) {
        for (auto z = 0; z < c.getDimensions()[2]; ++z) {
          auto pos = getPositionInContainer({x, y, z}, amount, *m);

          if (pos == -1) {
            continue;
          }

          Particle<3> &p = container.getParticles()[static_cast<unsigned long>(pos)];

          for (auto nx = x - 1; nx <= x + 1; ++nx) {
            for (auto ny = y - 1; ny <= y + 1; ++ny) {
              for (auto nz = z - 1; nz <= z + 1; ++nz) {
                if (nx < 0 || ny < 0 || nz < 0 || nx >= c.getDimensions()[0] || ny >= c.getDimensions()[1]
                    || nz >= c.getDimensions()[2]) {
                  continue;
                }

                auto neighbourPos = getPositionInContainer({nx, ny, nz}, amount, *m);

                if (neighbourPos <= pos || neighbourPos == -1) {
                  continue;
                }

                Particle<3> &neighbour = container.getParticles()[static_cast<unsigned long>(neighbourPos)];

                if ((x == nx && (y == ny || z == nz)) || (y == ny && z == nz)) {
                  p.addNeighbour(&neighbour);
                } else {
                  p.addDiagonalNeighbour(&neighbour);
                }
              }
            }
          }
        }
      }
    }
  }
}

template<>
void Generator<RectangularArgument<2>, 2>::generateRectangular(const RectangularArgument<2> &c,
                                                               ParticleContainer<2> &container) {

  int amount = static_cast<int>(container.size());

  if (c.getPacked()) {
    for (auto x = 0; x < c.getDimensions()[0]; ++x) {
      for (auto y = 0; y < c.getDimensions()[1]; ++y) {
        Vector<2> pos
            {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1]};
        Particle<2> p
            {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType(),
             c.isFixed()};
        linkForce(p, c.getForces(), std::array<int, 2>{x, y});
        applyMotion(c.getMeanValue(), p);

        if (auto *m = dynamic_cast<const MembraneArgument<2> *>(&c)) {
          p.setParticleTypeToMolecule();
          p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());
        }

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
        Particle<2> p
            {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType(),
             c.isFixed()};
        linkForce(p, c.getForces(), std::array<int, 2>{x, y});
        applyMotion(c.getMeanValue(), p);

        if (auto *m = dynamic_cast<const MembraneArgument<2> *>(&c)) {
          p.setParticleTypeToMolecule();
          p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());
        }

        container.addParticle(p);
      }
    }

    for (auto y: yMinMax) {
      for (int x = 1; x < c.getDimensions()[0] - 1; ++x) {
        Vector<2> pos
            {x * c.getDistance() + c.getStartingCoordinates()[0], y * c.getDistance() + c.getStartingCoordinates()[1]};
        Particle<2> p
            {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType(),
             c.isFixed()};
        linkForce(p, c.getForces(), std::array<int, 2>{x, y});
        applyMotion(c.getMeanValue(), p);

        if (auto *m = dynamic_cast<const MembraneArgument<2> *>(&c)) {
          p.setParticleTypeToMolecule();
          p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());
        }

        container.addParticle(p);
      }
    }
  }

  if (auto *m = dynamic_cast<const MembraneArgument<2> *>(&c)) {
    // Insert Particle pointer into vector
    for (auto i = static_cast<size_t>(amount); i < container.size(); ++i) {
      container.addMolecule(&container.getParticles()[i]);
    }

    // Fixed outline
    if (m->getFixedOutline()) {
      fixOutline(amount, *m, container);
    }

    for (auto x = 0; x < c.getDimensions()[0]; ++x) {
      for (auto y = 0; y < c.getDimensions()[1]; ++y) {
        auto pos = getPositionInContainer({x, y}, amount, *m);

        if (pos == -1) {
          continue;
        }

        Particle<2> &p = container.getParticles()[static_cast<unsigned long>(pos)];

        for (auto nx = x - 1; nx <= x + 1; ++nx) {
          for (auto ny = y - 1; ny <= y + 1; ++ny) {
            if (nx < 0 || ny < 0 || nx >= c.getDimensions()[0] || ny >= c.getDimensions()[1]) {
              continue;
            }

            auto neighbourPos = getPositionInContainer({nx, ny}, amount, *m);

            if (neighbourPos <= pos || neighbourPos == -1) {
              continue;
            }

            Particle<2> &neighbour = container.getParticles()[static_cast<unsigned long>(neighbourPos)];

            if (x == nx || y == ny) {
              p.addNeighbour(&neighbour);
            } else {
              p.addDiagonalNeighbour(&neighbour);
            }
          }
        }
      }
    }
  }
}

template<>
void Generator<RectangularArgument<3>, 3>::generate(const RectangularArgument<3> &c, ParticleContainer<3> &container) {
  SPDLOG_TRACE("Rectangular generated!");
  generateRectangular(c, container);
}

template<>
void Generator<RectangularArgument<2>, 2>::generate(const RectangularArgument<2> &c, ParticleContainer<2> &container) {
  SPDLOG_TRACE("Rectangular generated!");
  generateRectangular(c, container);
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

        Particle<3> p
            {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType(),
             c.isFixed()};
        linkForce(p, c.getForces(), std::array<int, 3>{x, y, z});
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

      Particle<2> p
          {pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(), c.getType(),
           c.isFixed()};
      linkForce(p, c.getForces(), std::array<int, 2>{x, y});
      applyMotion(c.getMeanValue(), p);
      container.addParticle(p);
    }
  }
}
