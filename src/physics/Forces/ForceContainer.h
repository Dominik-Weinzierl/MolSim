#pragma once

#include <ostream>

#include "Forces.h"

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
   * Force object applied on all indices.
   */
  Forces<dim> force;

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

  /**
   * Prints the ForceContainer.
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\t\t\t Additional Force: " << std::endl;
    argument << "\t\t\t\t\t\t Indices: " << std::endl;
    for (auto &index: indices) {
      argument << "\t\t\t\t\t\t\t Index: " << ArrayUtils::to_string(index) << std::endl;
    }
    argument << force << std::endl;
    return argument.str();
  };

  friend std::ostream &operator<<(std::ostream &os, const ForceContainer &container) {
    os << container.toString();
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
  [[nodiscard]] const Forces<dim> &getForce() const {
    return force;
  }
};