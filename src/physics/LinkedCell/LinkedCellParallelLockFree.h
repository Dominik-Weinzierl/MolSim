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

          // calc between particles in cells and relevant neighbours
          for (auto n = neighbours.begin(); n != neighbours.end(); ++n) {
            for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
              for (auto j = (*n)->getParticles().begin(); j != (*n)->getParticles().end(); ++j) {
                double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*(*i), *(*j));

                if (l2Norm > cellContainer.getCutoffRadiusSquare())
                  continue;

                SPDLOG_TRACE("Calculating force for {} and {}", (*i)->toString(), (*j)->toString());
                Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*(*i), *(*j), l2Norm)};
                (*i)->updateForce(force);
                (*j)->updateForce(-force);
              }
            }
          }

          // calc in the cells
          for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
            for (auto j = i + 1; j != cellParticles.end(); ++j) {
              SPDLOG_TRACE("Calculating force for {} and {}", (*i)->toString(), (*j)->toString());

              double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*(*i), *(*j));

              Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*(*i), *(*j), l2Norm)};

              (*i)->updateForce(force);
              (*j)->updateForce(-force);
            }
          }
        }
      }
    }

    // Periodic neighbours sequentially
    for (size_t c = 0; c < cellContainer.getBoundaryCells().size(); ++c) {
      Boundary<dim> &cell = cellContainer.getBoundaryCells()[c];
      std::vector<Particle<dim> *> &cellParticles = cell.getParticles();

      std::vector<std::tuple<Cell<dim> *, Vector<dim>>> &periodicNeighbours = cell.getPeriodicNeighbours();
      // calc periodic
      for (std::tuple<Cell<dim> *, Vector<dim>> &t: periodicNeighbours) {
        Cell<dim> *periodicCell = std::get<0>(t);

        if (!periodicCell->getParticles().empty()) {

          for (auto j = periodicCell->getParticles().begin(); j != periodicCell->getParticles().end(); ++j) {
            const Vector<dim> oldPos = (*j)->getX();
            Vector<dim> pos;
            for (size_t index = 0; index < dim; ++index) {
              pos[index] = oldPos[index] - periodicCell->getPosition()[index] + std::get<1>(t)[index];
            }
            (*j)->setX(pos);

            for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
              double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*(*i), *(*j));

              if (l2Norm > cellContainer.getCutoffRadiusSquare())
                continue;

              SPDLOG_TRACE("Calculating force for {} and {}", (*i)->toString(), (*j)->toString());
              Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*(*i), *(*j), l2Norm)};
              (*i)->updateForce(force);
              (*j)->updateForce(-force);
            }

            (*j)->setX(oldPos);
          }
        }
      }
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
