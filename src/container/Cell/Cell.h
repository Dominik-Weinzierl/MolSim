#pragma once

#include "particles/Particle.h"
#include <functional>
#include <boundaryType/BoundaryType.h>
#include <iostream>

template<size_t dim>
class Cell {
 protected:
  std::vector<Particle<dim> *> particles{};
  std::vector<Cell<dim> *> neighbours{};
  std::vector<Cell<dim> *> relevantNeighbours{};

  BoundaryType boundaryType = BoundaryType::Outflow;

 public:
  Cell() = default;
  Cell(BoundaryType pBoundaryType) : boundaryType{pBoundaryType} {};

  virtual ~Cell() = default;
  virtual void applyCellProperties() = 0;

  void insertParticle(Particle<dim> *p) {
    particles.push_back(p);
  }

  void moveParticleToAnotherCell(Particle<dim> *p, Cell<dim> *c) {
    particles.erase(std::remove(particles.begin(), particles.end(), p), particles.end());
    c->insertParticle(p);
  }

  /**
   * @return Iterator to the beginning of the particles-Vector.
   */
  [[nodiscard]] auto begin() { return particles.begin(); }

  /**
   * @return Iterator to the end of the particles-Vector.
   */
  [[nodiscard]] auto end() { return particles.end(); }

  /**
   * @return Iterator to the beginning of the neighbours-Vector.
   */
  [[nodiscard]] auto nBegin() { return neighbours.begin(); }

  /**
   * @return Iterator to the end of the neighbours-Vector.
   */
  [[nodiscard]] auto nEnd() { return neighbours.end(); }

  std::vector<Particle<dim> *> &getParticles() {
    return particles;
  }

  std::vector<Cell<dim> *> &getNeighbours() {
    return neighbours;
  }

  std::vector<Cell<dim> *> &getRelevantNeighbours() {
    return relevantNeighbours;
  }
};
