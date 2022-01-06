#include "generator/GeneratorArguments/SphereArgument.h"
#include "generator/GeneratorArguments/variants/CuboidArgument.h"
#include "generator/GeneratorArguments/variants/MembraneArgument.h"
#include "generator/Generator.h"


// TODO FIX and REFACTORING -> Avoid hard coding of values!
template<>
void Generator<RectangularArgument<3>, 3>::generateRectangular(const RectangularArgument<3> &t,
                                                               ParticleContainer<3> &container) {

  if (t.getPacked()) {
    if (auto *c = dynamic_cast<const CuboidArgument<3> *>(&t)) {
      for (auto x = 0; x < t.getDimensions()[0]; ++x) {
        for (auto y = 0; y < t.getDimensions()[1]; ++y) {
          for (auto z = 0; z < t.getDimensions()[2]; ++z) {
            Vector<3> pos
                {x * t.getDistance() + t.getStartingCoordinates()[0],
                 y * t.getDistance() + t.getStartingCoordinates()[1],
                 z * t.getDistance() + t.getStartingCoordinates()[2]};

            Particle<3> p
                {pos, c->getInitialVelocity(), c->getMass(), c->getZeroCrossing(), c->getDepthOfPotentialWell(),
                 c->getType()};
            applyMotion(c->getMeanValue(), p);
            container.addParticle(p);

          }
        }
      }
    } else if (auto *m = dynamic_cast<const MembraneArgument<3> *>(&t)) {

      std::vector<std::vector<std::vector<Particle<3> *>>> particlesCube;
      auto dimX = static_cast<size_t>(t.getDimensions()[0]);
      auto dimY = static_cast<size_t>(t.getDimensions()[1]);
      auto dimZ = static_cast<size_t>(t.getDimensions()[2]);
      for (size_t z = 0; z < dimZ; ++z) {

        std::vector<std::vector<Particle<3> *>> particlesMatrix;

        for (size_t x = 0; x < dimX; ++x) {

          std::vector<Particle<3> *> particlesCol;

          for (size_t y = 0; y < dimY; ++y) {

            Vector<3> pos
                {static_cast<double>(x) * t.getDistance() + t.getStartingCoordinates()[0],
                 static_cast<double>(y) * t.getDistance() + t.getStartingCoordinates()[1],
                 static_cast<double>(z) * t.getDistance() + t.getStartingCoordinates()[2]};

            Particle<3> p
                {pos, m->getInitialVelocity(), m->getMass(), m->getZeroCrossing(), m->getDepthOfPotentialWell(),
                 m->getType()};
            Particle<3> *pointer = &p;
            p.setParticleTypeToMolecule();
            p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());

            //TODO: Neighbours, DiagonalNeighbours
            particlesCol.emplace_back(pointer);

            if (z > 0) {
              if (x > 0) {
                if (y > 0 && y < dimY - 1) {
                  if (x < dimX - 1) {
                    p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y + 1]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y - 1]);
                  }
                  p.addNeighbour(particlesCol[y - 1]);
                  p.addDiagonalNeighbour(particlesMatrix[x - 1][y - 1]);
                  p.addDiagonalNeighbour(particlesMatrix[x - 1][y + 1]);
                  p.addDiagonalNeighbour(particlesCube[z - 1][x - 1][y]);
                  p.addDiagonalNeighbour(particlesCube[z - 1][x - 1][y + 1]);
                  p.addDiagonalNeighbour(particlesCube[z - 1][x][y + 1]);
                  p.addDiagonalNeighbour(particlesCube[z - 1][x - 1][y - 1]);
                  p.addDiagonalNeighbour(particlesCube[z - 1][x][y - 1]);
                } else if (y == 0 && dimY > 1) {
                  if (x < dimX - 1) {
                    p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y + 1]);
                  }
                  p.addDiagonalNeighbour(particlesMatrix[x - 1][y + 1]);
                  p.addDiagonalNeighbour(particlesCube[z - 1][x - 1][y]);
                  p.addDiagonalNeighbour(particlesCube[z - 1][x - 1][y + 1]);
                  p.addDiagonalNeighbour(particlesCube[z - 1][x][y + 1]);
                } else if (y == dimY - 1) {
                  if (dimY > 1) {
                    if (x < dimX - 1) {
                      p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y - 1]);
                      p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y]);
                    }
                    p.addNeighbour(particlesCol[y - 1]);
                    p.addDiagonalNeighbour(particlesMatrix[x - 1][y - 1]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x - 1][y - 1]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x][y - 1]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x - 1][y]);
                  } else {
                    if (x < dimX - 1) {
                      p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y]);
                    }
                    p.addNeighbour(particlesCol[y - 1]);
                    p.addDiagonalNeighbour(particlesMatrix[x - 1][y - 1]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x - 1][y]);
                  }
                }
                p.addNeighbour(particlesMatrix[x - 1][y]);
                p.addNeighbour(particlesCube[z - 1][x][y]);
              } else {
                if (dimX > 1) {
                  if (y > 0) {
                    p.addNeighbour(particlesCol[y - 1]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x][y - 1]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y - 1]);
                  }

                  if (y < dimY - 1) {
                    p.addDiagonalNeighbour(particlesCube[z - 1][x][y + 1]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y + 1]);
                  }
                  p.addDiagonalNeighbour(particlesCube[z - 1][x + 1][y]);

                } else {
                  if (y > 0) {
                    p.addNeighbour(particlesCol[y - 1]);
                    p.addDiagonalNeighbour(particlesCube[z - 1][x][y - 1]);
                  }

                  if (y < dimY - 1) {
                    p.addDiagonalNeighbour(particlesCube[z - 1][x][y + 1]);
                  }
                }
                p.addNeighbour(particlesCube[z - 1][x][y]);
              }
            } else {
              if (x > 0) {
                if (y > 0 && y < dimY - 1) {
                  p.addNeighbour(particlesCol[y - 1]);
                  p.addDiagonalNeighbour(particlesMatrix[x - 1][y - 1]);
                  p.addDiagonalNeighbour(particlesMatrix[x - 1][y + 1]);
                } else if (y == 0 && dimY > 1) {
                  p.addDiagonalNeighbour(particlesMatrix[x - 1][y + 1]);
                } else if (y == dimY - 1) {
                  p.addNeighbour(particlesCol[y - 1]);
                  p.addDiagonalNeighbour(particlesMatrix[x - 1][y - 1]);
                }
                p.addNeighbour(particlesMatrix[x - 1][y]);
              } else {
                if (y > 0) {
                  p.addNeighbour(particlesCol[y - 1]);
                }
              }
            }

            //TODO: Performancekritisch af
            for (auto f: container.getForces()) {
              for (auto &i: f.getIndices()) {
                if (i == pos) {
                  f.addAdditionalForceParticles(pointer);
                }
              }
            }

            applyMotion(m->getMeanValue(), p);
            container.addMolecule(pointer);
            container.addParticle(p);
          }
          particlesMatrix.emplace_back(particlesCol);
        }
        particlesCube.emplace_back(particlesMatrix);
      }
    }
  } else {
    std::array<int, 2> xMinMax{0, t.getDimensions()[0] - 1};
    std::array<int, 2> yMinMax{0, t.getDimensions()[1] - 1};
    std::array<int, 2> zMinMax{0, t.getDimensions()[2] - 1};

    if (auto *c = dynamic_cast<const CuboidArgument<3> *>(&t)) {
      for (auto x: xMinMax) {
        //TODO: alle t's ersetzen
        for (auto y = 0; y < c->getDimensions()[1]; ++y) {
          for (auto z = 0; z < t.getDimensions()[2]; ++z) {
            Vector<3> pos
                {x * t.getDistance() + t.getStartingCoordinates()[0],
                 y * t.getDistance() + t.getStartingCoordinates()[1],
                 z * t.getDistance() + t.getStartingCoordinates()[2]};
            Particle<3> p
                {pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(),
                 t.getType()};
            applyMotion(t.getMeanValue(), p
            );
            container.addParticle(p);
          }
        }
      }

      for (auto y: yMinMax) {
        for (auto x = 1; x < t.getDimensions()[0] - 1; ++x) {
          for (auto z = 0; z < t.getDimensions()[2]; ++z) {
            Vector<3> pos
                {x * t.getDistance() + t.getStartingCoordinates()[0],
                 y * t.getDistance() + t.getStartingCoordinates()[1],
                 z * t.getDistance() + t.getStartingCoordinates()[2]};
            Particle<3> p
                {pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(),
                 t.getType()};
            applyMotion(t.getMeanValue(), p);
            container.addParticle(p);
          }
        }
      }

      for (auto z: zMinMax) {
        for (auto x = 1; x < t.getDimensions()[0] - 1; ++x) {
          for (auto y = 1; y < t.getDimensions()[1] - 1; ++y) {
            Vector<3> pos
                {x * t.getDistance() + t.getStartingCoordinates()[0],
                 y * t.getDistance() + t.getStartingCoordinates()[1],
                 z * t.getDistance() + t.getStartingCoordinates()[2]};
            Particle<3> p
                {pos, t.getInitialVelocity(), t.getMass(), t.getZeroCrossing(), t.getDepthOfPotentialWell(),
                 t.getType()};
            applyMotion(t.getMeanValue(), p);
            container.addParticle(p);
          }
        }
      }
    }
//    else if(auto *m = dynamic_cast<const MembraneArgument<3> *>(&t)){
//      //TODO:
//    }
  }
}

template<>
void Generator<RectangularArgument<2>, 2>::generateRectangular(const RectangularArgument<2> &t,
                                                               ParticleContainer<2> &container) {
  if (t.getPacked()) {

    if (auto *c = dynamic_cast<const CuboidArgument<2> *>(&t)) {
      for (auto x = 0; x < t.getDimensions()[0]; ++x) {
        for (auto y = 0; y < t.getDimensions()[1]; ++y) {

          Vector<2> pos
              {x * t.getDistance() + t.getStartingCoordinates()[0],
               y * t.getDistance() + t.getStartingCoordinates()[1]};

          Particle<2> p{pos, c->getInitialVelocity(), c->getMass(), c->getZeroCrossing(), c->getDepthOfPotentialWell(),
                        c->getType()};
          applyMotion(c->getMeanValue(), p);
          container.addParticle(p);
        }
      }

    } else if (auto *m = dynamic_cast<const MembraneArgument<2> *>(&t)) {

      std::vector<std::vector<Particle<2> *>> particlesMatrix;
      auto dimX = static_cast<size_t>(t.getDimensions()[0]);
      auto dimY = static_cast<size_t>(t.getDimensions()[1]);

      for (size_t x = 0; x < dimX; ++x) {
        std::vector<Particle<2> *> particlesCol;
        for (size_t y = 0; y < dimY; ++y) {

          Vector<2> pos
              {static_cast<double>(x) * t.getDistance() + t.getStartingCoordinates()[0],
               static_cast<double>(y) * t.getDistance() + t.getStartingCoordinates()[1]};

          Particle<2> p{pos, m->getInitialVelocity(), m->getMass(), m->getZeroCrossing(), m->getDepthOfPotentialWell(),
                        m->getType()};
          Particle<2> *pointer = &p;
          p.setParticleTypeToMolecule();
          p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());

          //TODO: Neighbours, DiagonalNeighbours
          particlesCol.emplace_back(pointer);
          if (x > 0) {
            if (y > 0 && y < dimY - 1) {
              p.addNeighbour(particlesCol[y - 1]);
              p.addDiagonalNeighbour(particlesMatrix[x - 1][y - 1]);
              p.addDiagonalNeighbour(particlesMatrix[x - 1][y + 1]);
            } else if (y == 0 && dimY > 1) {
              p.addDiagonalNeighbour(particlesMatrix[x - 1][y + 1]);
            } else if (y == dimY - 1) {
              p.addNeighbour(particlesCol[y - 1]);
              p.addDiagonalNeighbour(particlesMatrix[x - 1][y - 1]);
            }
            p.addNeighbour(particlesMatrix[x - 1][y]);
          } else {
            if (y > 0) {
              p.addNeighbour(particlesCol[y - 1]);
            }
          }

          //TODO: Performancekritisch af
          for (auto f: container.getForces()) {
            for (auto &i: f.getIndices()) {
              if (i == pos) {
                f.addAdditionalForceParticles(pointer);
              }
            }
          }

          applyMotion(m->getMeanValue(), p);
          container.addMolecule(pointer);
          container.addParticle(p);

        }
        particlesMatrix.emplace_back(particlesCol);
      }
    }
  } else {
    std::array<int, 2> xMinMax{0, t.getDimensions()[0] - 1};
    std::array<int, 2> yMinMax{0, t.getDimensions()[1] - 1};

    //t is either Cuboid or Membrane, else if not necessary but I think it's nice to check anyways :)
    if (auto *c = dynamic_cast<const CuboidArgument<2> *>(&t)) {
      for (auto x: xMinMax) {
        for (int y = 0; y < c->getDimensions()[1]; ++y) {
          Vector<2> pos
              {x * c->getDistance() + c->getStartingCoordinates()[0],
               y * c->getDistance() + c->getStartingCoordinates()[1]};
          Particle<2>
              p{pos, c->getInitialVelocity(), c->getMass(), c->getZeroCrossing(), c->getDepthOfPotentialWell(),
                c->getType()};
          applyMotion(c->getMeanValue(), p);
          container.addParticle(p);
        }
      }

      for (auto y: yMinMax) {
        for (int x = 1; x < c->getDimensions()[0] - 1; ++x) {
          Vector<2> pos
              {x * c->getDistance() + c->getStartingCoordinates()[0],
               y * c->getDistance() + c->getStartingCoordinates()[1]};
          Particle<2>
              p{pos, c->getInitialVelocity(), c->getMass(), c->getZeroCrossing(), c->getDepthOfPotentialWell(),
                c->getType()};
          applyMotion(c->getMeanValue(), p);
          container.addParticle(p);
        }
      }
    } else if (auto *m = dynamic_cast<const MembraneArgument<2> *>(&t)) {

      //Needed in order to get all neighbours for the y-for-loop
      std::vector<Particle<2> *> linkingParticles{};

      // Vx1 Edge-Case
      if (t.getDimensions()[1] > 1) {

        for (auto x: xMinMax) {

          //Pointer to get to previously generated Particle
          Particle<2> *prev;

          for (int y = 0; y < m->getDimensions()[1]; ++y) {
            Vector<2> pos
                {x * m->getDistance() + m->getStartingCoordinates()[0],
                 y * m->getDistance() + m->getStartingCoordinates()[1]};

            Particle<2>
                p{pos, m->getInitialVelocity(), m->getMass(), m->getZeroCrossing(), m->getDepthOfPotentialWell(),
                  m->getType()};
            p.setParticleTypeToMolecule();
            p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());

            Particle<2> *pointer = &p;

            //TODO: Performancekritisch af, mach extra methode du spast
            for (auto f: container.getForces()) {
              for (auto &i: f.getIndices()) {
                if (i == pos) {
                  f.addAdditionalForceParticles(pointer);
                }
              }
            }

            //TODO: Neighbours, DiagonalNeighbours
            if (y == 0) {
              prev = &p;
              continue;
            }

            // Vx2 Edge-Case
            if (y == 1) {
              linkingParticles.emplace_back(pointer);
            }
            if (y == m->getDimensions()[1] - 1) {
              linkingParticles.emplace_back(pointer);
            }

            p.addNeighbour(prev);
            prev = &p;

            applyMotion(m->getMeanValue(), p);
            container.addMolecule(pointer);
            container.addParticle(p);
          }
        }

        if (t.getDimensions()[0] == 2) {

          Particle<2> *previous = nullptr;
          Particle<2> *current = linkingParticles[1];
          //TODO: wasch da los
          Particle<2> *next = linkingParticles[1]->getNeighbours()[0];

          Particle<2> *iterator = linkingParticles[3];

          for (auto i = t.getDimensions()[1]; i > 0; i--) {
            iterator->addNeighbour(current);
            if (i == 1) {
              iterator->addDiagonalNeighbour(previous);
              continue;
            } else if (i == t.getDimensions()[1]) {
              iterator->addDiagonalNeighbour(next);
            } else {
              iterator->addDiagonalNeighbour(previous);
              iterator->addDiagonalNeighbour(next);
            }

            previous = current;
            current = next;
            next = next->getNeighbours()[0];

            iterator = iterator->getNeighbours()[0];

          }

        } else {

          //Vx2 Edge-case
          Particle<2> *bottomY = nullptr;

          for (auto y: yMinMax) {

            Particle<2> *prev;

            for (int x = 1; x < t.getDimensions()[0] - 1; ++x) {
              Vector<2> pos
                  {x * m->getDistance() + m->getStartingCoordinates()[0],
                   y * m->getDistance() + m->getStartingCoordinates()[1]};

              Particle<2>
                  p{pos, m->getInitialVelocity(), m->getMass(), m->getZeroCrossing(), m->getDepthOfPotentialWell(),
                    m->getType()};
              p.setParticleTypeToMolecule();
              p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());

              Particle<2> *pointer = &p;

              //TODO: Performancekritisch af, mach extra methode du spast
              for (auto f: container.getForces()) {
                for (auto &i: f.getIndices()) {
                  if (i == pos) {
                    f.addAdditionalForceParticles(pointer);
                  }
                }
              }

              //TODO: Neighbours, DiagonalNeighbours
              if (x == 1) {
                prev = &p;
                if (y == 0) {
                  bottomY = pointer;
                  p.addNeighbour(linkingParticles[0]->getNeighbours()[0]);
                  p.addDiagonalNeighbour(linkingParticles[0]);
                } else {
                  p.addNeighbour(linkingParticles[1]);
                  p.addDiagonalNeighbour(linkingParticles[1]->getNeighbours()[0]);
                }

                continue;
              }

              if (x == t.getDimensions()[0] - 2) {
                if (y == 0) {
                  p.addNeighbour(linkingParticles[2]->getNeighbours()[0]);
                  p.addDiagonalNeighbour(linkingParticles[2]);
                } else {
                  p.addNeighbour(linkingParticles[3]);
                  p.addDiagonalNeighbour(linkingParticles[3]->getNeighbours()[0]);
                }
              }

              p.addNeighbour(prev);
              if (y == 1 && t.getDimensions()[1] == 2) {

                //TODO: linkingEdgeCaseHelper(particlepointer, particlepointer, dimensionLength);
                Particle<2> *previous = nullptr;
                Particle<2> *current = bottomY;
                Particle<2> *next = bottomY->getNeighbours()[0];

                Particle<2> *iterator = pointer;

                for (auto i = t.getDimensions()[0] - 1; i > 1; i--) {
                  iterator->addNeighbour(current);
                  if (i == 1) {
                    iterator->addDiagonalNeighbour(previous);
                    continue;
                  } else if (i == t.getDimensions()[1]) {
                    iterator->addDiagonalNeighbour(next);
                  } else {
                    iterator->addDiagonalNeighbour(previous);
                    iterator->addDiagonalNeighbour(next);
                  }

                  previous = current;
                  current = next;
                  next = next->getNeighbours()[0];
                }
                prev = &p;
              }

              applyMotion(m->getMeanValue(), p);
              container.addMolecule(pointer);
              container.addParticle(p);
            }
          }
        }
      } else {

        //Pointer to get to previously generated Particle
        Particle<2> *prev;

        for (int x = 0; x < m->getDimensions()[0]; ++x) {
          Vector<2> pos
              {x * m->getDistance() + m->getStartingCoordinates()[0],
               m->getStartingCoordinates()[1]};

          Particle<2>
              p{pos, m->getInitialVelocity(), m->getMass(), m->getZeroCrossing(), m->getDepthOfPotentialWell(),
                m->getType()};
          p.setParticleTypeToMolecule();
          p.setMembraneArguments(m->getStiffness(), m->getAverageBondLength());

          Particle<2> *pointer = &p;

          //TODO: Performancekritisch af, mach extra methode du spast
          for (auto f: container.getForces()) {
            for (auto &i: f.getIndices()) {
              if (i == pos) {
                f.addAdditionalForceParticles(pointer);
              }
            }
          }

          //TODO: Neighbours, DiagonalNeighbours
          if (x == 0) {
            prev = &p;
            continue;
          }

          p.addNeighbour(prev);
          prev = &p;

          applyMotion(m->getMeanValue(), p);
          container.addMolecule(pointer);
          container.addParticle(p);
        }
      }
    }
  }
}

template<>
void Generator<RectangularArgument<3>, 3>::generate(const RectangularArgument<3> &c,
                                                    ParticleContainer<3> &container) {
  SPDLOG_TRACE("Rectangular generated!");
  generateRectangular(c, container);
}

template<>
void Generator<RectangularArgument<2>, 2>::generate(const RectangularArgument<2> &c,
                                                    ParticleContainer<2> &container) {
  SPDLOG_TRACE("Rectangular generated!");
  generateRectangular(c, container);
}

template<>
void Generator<SphereArgument<3>, 3>::generate(const SphereArgument<3> &c, ParticleContainer<3> &container) {
  SPDLOG_TRACE("Sphere generated!");
  double rad = c.getRadius() * c.getDistance();
  std::array<double, 3>
      corner
      {c.getCenterCoordinates()[0] - rad, c.getCenterCoordinates()[1] - rad, c.getCenterCoordinates()[2] - rad};
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
            p{pos, c.getInitialVelocity(), c.getMass(), c.getZeroCrossing(), c.getDepthOfPotentialWell(),
              c.getType(), c.isFixed()};
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
      applyMotion(c.getMeanValue(), p);
      container.addParticle(p);
    }
  }
}
