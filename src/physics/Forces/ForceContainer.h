#pragma once

#include <ostream>

#include "Force.h"

/**
 * Wrapper for xsd-force_t.
 * @tparam dim dimension of the Vectors
 */
template<size_t dim>
class ForceContainer {
 private:

  /**
   * Vector of indices.
   * Empty if force should be applied to all particles.
   */
  std::vector<std::array<int, dim>> indices;

  /**
   *
   */
  Force<dim> force;

 public:

  /**
   * Constructor for ForceContainer.
   * @param pIndices indices to apply force to
   * @param pForce force to apply
   * @param pStartTime start time of the force
   * @param pEndTime end time of the force
   */
  ForceContainer(std::vector<std::array<int, dim>> pIndices, Vector<dim> pForce, unsigned int pStartTime,
                 unsigned int pEndTime) : indices{pIndices}, force{pForce, pStartTime, pEndTime} {}

  //----------------------------------------Methods----------------------------------------


  friend std::ostream &operator<<(std::ostream &os, const ForceContainer &f) {
    (void) f;
    os << "indices: ";
    return os;
  }

  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * Getter for indices.
   * @return indices
   */
  [[nodiscard]] const std::vector<std::array<int, dim>> &getIndices() const {
    return indices;
  }

  /**
   * Getter for force.
   * @return force
   */
  [[nodiscard]] const Force<dim> &getForce() const {
    return force;
  }
};