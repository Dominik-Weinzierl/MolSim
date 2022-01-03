#pragma once

#include "physics/Physics.h"
#include "physics/variants/LennardJones.h"
#include "container/LinkedCell/LinkedCellContainer.h"
#include "physics/Forces/Forces.h"
#include "LinkedCell.h"

/**
 * This class implements the LinkedCell algorithm.
 * @tparam T The physics to be used.
 * @tparam dim The dimension of our simulation
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class LinkedCellParallelLockFree : LinkedCell<T, dim> {
 public:
  LinkedCellParallelLockFree() = default;

  //----------------------------------------Methods----------------------------------------

  void performUpdate(ParticleContainer<dim> &particleContainer) const override;

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
  */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, double &force) const override {
    LinkedCell<T, dim>::calculateNextStep(particleContainer, deltaT, force);
  }
};

/**
 * Implements LinkedCell for LennardJones
 * @tparam dim The dimension of our simulation
 */
template<size_t dim>
class LinkedCellParallelLockFree<LennardJones, dim> : public LinkedCell<LennardJones, dim> {
 private:
  std::vector<std::vector<Cell<dim> *>> cells;

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
  LinkedCellParallelLockFree() = default;
  LinkedCellParallelLockFree(double cutoffRadius, Vector<dim> cellSize, ParticleContainer<dim> &particleContainer);

  //----------------------------------------Methods----------------------------------------

  void performUpdate(ParticleContainer<dim> &particleContainer) const override {
    auto &cellContainer = static_cast<LinkedCellContainer<dim> &>(particleContainer);

#pragma omp parallel for shared(cellContainer) default(none)
    for (size_t i = 0; i < cellContainer.getBoundaryCells().size(); ++i) {
      Boundary<dim> &b = cellContainer.getBoundaryCells()[i];
      b.applyCellProperties();
    }

    for (auto &cellVector: cells) {
#pragma omp parallel for shared(cellVector, cellContainer) default(none)
      for (size_t c = 0; c < cellVector.size(); ++c) {

        Cell<dim> *cell = cellVector[c];
        std::vector<Cell<dim> *> &neighbours = cell->getNeighbours();
        std::vector<Particle<dim> *> &cellParticles = cell->getParticles();

        if (!cellParticles.empty()) {

          LinkedCell<LennardJones, dim>::calcBetweenNeighboursAndCell(neighbours, cellParticles, cellContainer);

          LinkedCell<LennardJones, dim>::calcInTheCell(cellParticles);
        }
      }
    }

    // Periodic neighbours sequentially
    for (size_t c = 0; c < cellContainer.getBoundaryCells().size(); ++c) {
      Boundary<dim> &cell = cellContainer.getBoundaryCells()[c];
      std::vector<Particle<dim> *> &cellParticles = cell.getParticles();

      LinkedCell<LennardJones, dim>::calcPeriodic(cellParticles, cellContainer, cell);
    }
  }

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
  */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, double &force) const override {
    LinkedCell<LennardJones, dim>::calculateNextStep(particleContainer, deltaT, force);
  }
};
