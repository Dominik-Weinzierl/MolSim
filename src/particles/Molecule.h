#pragma once

#include "Particle.h"

template<size_t dim>
class Molecule : public Particle<dim> {

 private:
  std::vector<std::unique_ptr<Molecule<dim>>> neighbours;

 public:

  /**
   * Adds a molecule-pointer to neighbours.
   * @param p molecule-pointer
   */
  void addNeighbour(std::unique_ptr<Molecule<dim>> p){
    neighbours.template emplace_back(p);
  }

  /**
   * Getter for neighbours.
   * @return neighbours
   */
  [[nodiscard]] const std::vector<std::unique_ptr<Molecule<dim>>> &getNeighbours() const {
    return neighbours;
  }
};