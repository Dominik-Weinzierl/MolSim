#pragma once

#include "physics/Physics.h"
#include "physics/variants/LennardJones.h"
#include "container/LinkedCell/LinkedCellContainer.h"
#include "LinkedCell.h"

/**
 * This class implements the linked cell algorithm in the form of a parallel algorithm that works without locks.
 * @tparam T The physics to be used.
 * @tparam dim The dimension of our simulation
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class LinkedCellParallelLockFree : LinkedCell<T, dim> {
 public:
  //----------------------------------------Constructor----------------------------------------

  /**
   * Default constructor.
   */
  LinkedCellParallelLockFree() = default;

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
class LinkedCellParallelLockFree<LennardJones, dim> : public LinkedCell<LennardJones, dim> {
 protected:
  /**
   * This vector contains vectors of cells.
   * Each vector of cells contains independent cells and can be used in parallel without using locks.
   */
  std::vector<std::vector<Cell<dim> *>> cells;

  /**
   * This method checks the correctness of the list of vectors. It checks that each cell occurs only once.
   * @param cellContainer that provides possible required values and functionalities
   */
  inline void checkCorrectness(LinkedCellContainer<dim> &cellContainer) {
    for (auto &cellVector: cells) {
      for (auto &other: cells) {
        if (other == cellVector)
          continue;
        for (Cell<dim> *cell: cellVector) {
          if (std::find(other.begin(), other.end(), cell) != other.end()) {
            // We evaluate one cell twice -> bad
            throw std::invalid_argument("One cell twice!");
          }
          for (Cell<dim> *otherCell: cellVector) {
            if (otherCell == cell)
              continue;

            if (std::find(cell->getNeighbours().begin(), cell->getNeighbours().end(), otherCell)
                != cell->getNeighbours().end()) {
              // Access one the same cell can cause issues
              throw std::invalid_argument("Neighbour is other cell -> bad!");
            }

            for (Cell<dim> *n: otherCell->getNeighbours()) {
              if (std::find(cell->getNeighbours().begin(), cell->getNeighbours().end(), n)
                  != cell->getNeighbours().end()) {
                // Access one the same cell can cause issues
                throw std::invalid_argument("Access on the same neighbour -> bad!");
              }
            }
          }
        }
      }
    }

    for (auto *boundaryAndInner: cellContainer.getBoundaryAndInnerCells()) {
      bool found = false;
      for (auto &cellVector: cells) {
        if (std::find(cellVector.begin(), cellVector.end(), boundaryAndInner) != cellVector.end()) {
          found = true;
          break;
        }
      }

      if (!found) {
        throw std::invalid_argument("Missing cell!");
      }
    }
  }

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * Default constructor
   */
  LinkedCellParallelLockFree() = default;

  /**
   * Constructor which provides the required values and create the required vector structure.
   * @param cutoffRadius of the linked cell structure
   * @param cellSize of the linked cell structure
   * @param particleContainer that provides possible required values and functionalities
   */
  LinkedCellParallelLockFree(double cutoffRadius, Vector<dim> cellSize, ParticleContainer<dim> &particleContainer);

  //----------------------------------------Methods----------------------------------------

  /**
   * This method calculates the forces between the different particles in the different cells.
   * @param particleContainer that provides possible required values and functionalities
   */
  void performUpdate(ParticleContainer<dim> &particleContainer) const override {
    auto &cellContainer = static_cast<LinkedCellContainer<dim> &>(particleContainer);

#pragma omp parallel for shared(cellContainer) default(none)  schedule(static, 8)
    for (size_t i = 0; i < cellContainer.getBoundaryCells().size(); ++i) {
      Boundary<dim> &b = cellContainer.getBoundaryCells()[i];
      b.applyCellProperties();
    }

    for (auto &cellVector: cells) {
#pragma omp parallel for shared(cellVector, cellContainer) default(none)  schedule(static, 8)
      for (size_t c = 0; c < cellVector.size(); ++c) {

        Cell<dim> *cell = cellVector[c];
        std::vector<Cell<dim> *> &neighbours = cell->getNeighbours();
        std::vector<Particle<dim> *> &cellParticles = cell->getParticles();

        if (!cellParticles.empty()) {

          LinkedCell<LennardJones, dim>::calcBetweenNeighboursAndCell(neighbours, cellParticles, cellContainer);

          LinkedCell<LennardJones, dim>::calcInTheCell(cellParticles, cellContainer);
        }
      }
    }

    // Periodic neighbours sequentially
    for (size_t c = 0; c < cellContainer.getBoundaryAndInnerCells().size(); ++c) {
      Cell<dim>* cell = cellContainer.getBoundaryAndInnerCells()[c];
      std::vector<Particle<dim> *> &cellParticles = cell->getParticles();

      LinkedCell<LennardJones, dim>::calcPeriodic(cellParticles, cellContainer, *cell);
    }

    LinkedCell<LennardJones, dim>::calculateMolecules(cellContainer);
  }

  /**
   * This method calculates the force, position and velocity of the particles in the container.
   * In addition, the structure is updated appropriately and renewed if needed.
   * Particles that leave the structure are deleted.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
   * @param gravitation additional vector of gravitational force applied on all particles
   * @param current_time current time of this iteration
   */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, Vector<dim> &gravitation,
                         double current_time) const override {
    LinkedCell<LennardJones, dim>::calculateNextStep(particleContainer, deltaT, gravitation, current_time);
  }
};
