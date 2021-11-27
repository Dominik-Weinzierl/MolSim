#pragma once

#include "boundaryConditions/BoundaryCondition.h"
#include "particles/Particle.h"
#include <functional>

template<typename T, size_t dim, typename std::enable_if<std::is_base_of<BoundaryCondition, T>::value,
                                                         bool>::type = true>
class Cell {
 protected:
  std::vector<std::reference_wrapper<Particle<dim>>> particles{};
  std::vector<std::reference_wrapper<Cell<T, dim>>> relevantNeighbours{};
 public:
  virtual void applyCellProperties(T &t) = 0;

  void insertParticle(Particle<dim> &p) {
    particles.push_back(p);
  }

  void moveParticleToAnotherCell(Particle<dim> &p, Cell<T, dim> &c) {
    particles.erase(std::remove(particles.begin(), particles.end(), p), particles.end());
    c.insertParticle(p);
  }
};