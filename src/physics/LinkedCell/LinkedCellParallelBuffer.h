#pragma once

#include "physics/Physics.h"
#include "physics/variants/LennardJones.h"
#include "container/LinkedCell/LinkedCellContainer.h"
#include "LinkedCell.h"

/**
 * This class implements the linked cell algorithm in the form of a parallel algorithm that works with buffer and without locks.
 * @tparam T The physics to be used
 * @tparam dim The dimension of our simulation
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class LinkedCellParallelBuffer : LinkedCell<T, dim> {
 public:
  LinkedCellParallelBuffer() = default;

  //----------------------------------------Methods----------------------------------------

  /**
   * This method calculates the forces between the different particles in the different cells.
   * @param particleContainer that provides possible required values and functionalities
   */
  void performUpdate(ParticleContainer<dim> &particleContainer) const override;

  /**
   * This method calculates the force, position and velocity of the particles in the container.
   * In addition, the structure is updated appropriately and renewed if needed.
   * Particles that leave the structure are deleted.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated
   * @param deltaT time step of our simulation
   * @param gravitation additional vector of gravitational force applied on all particles
   * @param current_time current time of this iteration
   */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, double &gravitation,
                         double current_time) const override {
    LinkedCell<T, dim>::calculateNextStep(particleContainer, deltaT, gravitation, current_time);
  }
};

/**
 * This class implements the linked cell algorithm in the form of a parallel algorithm that works with buffer and without locks.
 * @tparam dim The dimension of our simulation
 */
template<size_t dim>
class LinkedCellParallelBuffer<LennardJones, dim> : public LinkedCell<LennardJones, dim> {
 public:
  LinkedCellParallelBuffer() = default;

  //----------------------------------------Methods----------------------------------------

  /**
   * This method calculates the forces between the different particles in the different cells.
   * @param particleContainer that provides possible required values and functionalities
   */
  void performUpdate(ParticleContainer<dim> &particleContainer) const override {
    auto &cellContainer = static_cast<LinkedCellContainer<dim> &>(particleContainer);

#pragma omp declare reduction (merge : std::vector<std::pair<Particle<dim> *, Vector<dim>>> : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))

    // particle and value
    std::vector<std::pair<Particle<dim> *, Vector<dim>>> updates;

#pragma omp parallel for shared(cellContainer) default(none)
    for (size_t i = 0; i < cellContainer.getBoundaryCells().size(); ++i) {
      Boundary<dim> &b = cellContainer.getBoundaryCells()[i];
      b.applyCellProperties();
    }

#pragma omp parallel for shared(cellContainer) default(none) reduction(merge: updates)
    for (size_t c = 0; c < cellContainer.getBoundaryAndInnerCells().size(); ++c) {

      Cell<dim> *cell = cellContainer.getBoundaryAndInnerCells()[c];
      std::vector<Cell<dim> *> &neighbours = cell->getNeighbours();
      std::vector<Particle<dim> *> &cellParticles = cell->getParticles();

      if (!cellParticles.empty()) {

        // Calc between particles in cells and relevant neighbours
        for (auto n = neighbours.begin(); n != neighbours.end(); ++n) {
          for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
            for (auto j = (*n)->getParticles().begin(); j != (*n)->getParticles().end(); ++j) {
              Vector<dim> force = LinkedCell<LennardJones, dim>::calculateLennardJones(*(*i), *(*j), cellContainer);
              if (!isNull(force)) {
                (*i)->updateForce(force);
                updates.emplace_back(*j, -force);
              }
            }
          }
        }

        // Calc in the cells
        for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
          for (auto j = i + 1; j != cellParticles.end(); ++j) {
            Vector<dim> force = LinkedCell<LennardJones, dim>::calculateLennardJones(*(*i), *(*j), cellContainer);
            if (!isNull(force)) {
              (*i)->updateForce(force);
              updates.emplace_back(*j, -force);
            }
          }
        }
      }
    }

    for (auto &u: updates) {
      u.first->updateForce(u.second);
    }

    // Periodic neighbours sequentially
    for (size_t c = 0; c < cellContainer.getBoundaryCells().size(); ++c) {
      Boundary<dim> &cell = cellContainer.getBoundaryCells()[c];
      std::vector<Particle<dim> *> &cellParticles = cell.getParticles();

      LinkedCell<LennardJones, dim>::calcPeriodic(cellParticles, cellContainer, cell);
    }

    LinkedCell<LennardJones, dim>::calculateMolecules(cellContainer);
  }

  /**
   * This method calculates the force, position and velocity of the particles in the container.
   * In addition, the structure is updated appropriately and renewed if needed.
   * Particles that leave the structure are deleted.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated
   * @param deltaT time step of our simulation
   * @param gravitation additional vector of gravitational force applied on all particles
   * @param current_time current time of this iteration
   */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, Vector<dim> &gravitation,
                         double current_time) const override {
    LinkedCell<LennardJones, dim>::calculateNextStep(particleContainer, deltaT, gravitation, current_time);
  }
};
