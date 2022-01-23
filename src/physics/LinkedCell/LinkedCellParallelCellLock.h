#pragma once

#include <omp.h>

#include "physics/Physics.h"
#include "physics/variants/LennardJones.h"
#include "container/LinkedCell/LinkedCellContainer.h"
#include "LinkedCell.h"

/**
 * This class implements the linked cell algorithm in the form of a parallel algorithm that works with locks.
 * @tparam T The physics to be used
 * @tparam dim The dimension of our simulation
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class LinkedCellParallelCellLock : LinkedCell<T, dim> {
 public:
  //----------------------------------------Constructor----------------------------------------

  /**
   * Default constructor.
   */
  LinkedCellParallelCellLock() = default;

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
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
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
 * This class implements the linked cell algorithm in the form of a parallel algorithm that works without locks.
 * @tparam dim The dimension of our simulation
 */
template<size_t dim>
class LinkedCellParallelCellLock<LennardJones, dim> : public LinkedCell<LennardJones, dim> {
 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * Default constructor
   */
  LinkedCellParallelCellLock() = default;

  //----------------------------------------Methods----------------------------------------

  /**
   * This method calculates the forces between the different particles in the different cells.
   * @param particleContainer that provides possible required values and functionalities
   */
  void performUpdate(ParticleContainer<dim> &particleContainer) const override {
    auto &cellContainer = static_cast<LinkedCellContainer<dim> &>(particleContainer);

#pragma omp parallel for shared(cellContainer) default(none) schedule(static, 8)
    for (size_t i = 0; i < cellContainer.getBoundaryCells().size(); ++i) {
      Boundary<dim> &b = cellContainer.getBoundaryCells()[i];
      b.applyCellProperties();
    }

#pragma omp parallel for shared(cellContainer) default(none) schedule(static, 4)
    for (size_t c = 0; c < cellContainer.getBoundaryAndInnerCells().size(); ++c) {
      Cell<dim> *cell = cellContainer.getBoundaryAndInnerCells()[c];

      std::vector<Cell<dim> *> &neighbours = cell->getNeighbours();
      std::vector<Particle<dim> *> &cellParticles = cell->getParticles();

      if (!cellParticles.empty()) {
        // calc between particles in cells and relevant neighbours
        cell->setLock();
        for (auto n = neighbours.begin(); n != neighbours.end(); ++n) {
          (*n)->setLock();
          for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
            for (auto j = (*n)->getParticles().begin(); j != (*n)->getParticles().end(); ++j) {
              auto force = LinkedCell<LennardJones, dim>::calculateLennardJones(*(*i), *(*j), cellContainer);
              LinkedCell<LennardJones, dim>::updateForceForParticle(*(*i), *(*j), force);
            }
          }
          (*n)->unsetLock();
        }
        cell->unsetLock();

        cell->setLock();
        LinkedCell<LennardJones, dim>::calcInTheCell(cellParticles, cellContainer);
        cell->unsetLock();

        std::vector<std::tuple<Cell<dim> *, Vector<dim>>> &periodicNeighbours = cell->getPeriodicNeighbours();

        // Iterate over all periodic neighbours
        for (std::tuple<Cell<dim> *, Vector<dim>> &t: periodicNeighbours) {
          // Get the periodic cell which influences the current cell
          Cell<dim> *periodicCell = std::get<0>(t);

          if (!periodicCell->getParticles().empty()) {
            periodicCell->setLock();

            for (auto j = periodicCell->getParticles().begin(); j != periodicCell->getParticles().end(); ++j) {
              // Update the current position of the Particle(s)
              const Vector<dim> oldPos = (*j)->getX();
              Vector<dim> pos;
              for (size_t index = 0; index < dim; ++index) {
                pos[index] = oldPos[index] - periodicCell->getPosition()[index] + std::get<1>(t)[index];
              }
              (*j)->setX(pos);

              cell->setLock();
              for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
                auto force = LinkedCell<LennardJones, dim>::calculateLennardJones(*(*i), *(*j), cellContainer);
                LinkedCell<LennardJones, dim>::updateForceForParticle(*(*i), *(*j), force);
              }
              cell->unsetLock();

              (*j)->setX(oldPos);
            }
            periodicCell->unsetLock();
          }
        }
      }
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
