#pragma once

#include "physics/Physics.h"
#include "physics/variants/LennardJones.h"
#include "container/LinkedCell/LinkedCellContainer.h"
#include "LinkedCell.h"

/**
 * This class implements the LinkedCell algorithm.
 * @tparam T The physics to be used.
 * @tparam dim The dimension of our simulation
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class LinkedCellParallelBuffer : LinkedCell<T, dim> {
 public:
  LinkedCellParallelBuffer() = default;

  //----------------------------------------Methods----------------------------------------

  void performUpdate(ParticleContainer<dim> &particleContainer) const override;

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
  */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, double &gravitation,
                         double current_time) const override {
    LinkedCell<T, dim>::calculateNextStep(particleContainer, deltaT, gravitation, current_time);
  }
};

/**
 * Implements LinkedCell for LennardJones
 * @tparam dim The dimension of our simulation
 */
template<size_t dim>
class LinkedCellParallelBuffer<LennardJones, dim> : public LinkedCell<LennardJones, dim> {
 public:
  LinkedCellParallelBuffer() = default;

  //----------------------------------------Methods----------------------------------------

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

        // calc between particles in cells and relevant neighbours
        for (auto n = neighbours.begin(); n != neighbours.end(); ++n) {
          for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
            for (auto j = (*n)->getParticles().begin(); j != (*n)->getParticles().end(); ++j) {
              double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*(*i), *(*j));

              if (l2Norm > cellContainer.getCutoffRadiusSquare())
                continue;

              if ((*i)->getParticleType() == MOLECULE && (*j)->getParticleType() == MOLECULE
                  && (*i)->getType() == (*j)->getType()) {
                LinkedCell<LennardJones, dim>::calculateMoleculeForce((*i), (*j), l2Norm);

                //Checks if distance of i and j is greater => nextParticle, else apply lennardJones
                if (l2Norm > (LinkedCell<LennardJones, dim>::sixthSqrtOfTwo * (*i)->getZeroCrossing()
                    * LinkedCell<LennardJones, dim>::sixthSqrtOfTwo * (*i)->getZeroCrossing()))
                  continue;
              }

              SPDLOG_TRACE("Calculating force for {} and {}", (*i)->toString(), (*j)->toString());
              Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*(*i), *(*j), l2Norm)};

              (*i)->updateForce(force);
              updates.emplace_back(*j, -force);
            }
          }
        }

        // calc in the cells
        for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
          for (auto j = i + 1; j != cellParticles.end(); ++j) {
            SPDLOG_TRACE("Calculating force for {} and {}", (*i)->toString(), (*j)->toString());

            double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*(*i), *(*j));

            //TODO Pass ParticlePointer to function?
            LinkedCell<LennardJones, dim>::calculateMoleculeForce((*i), (*j), l2Norm);

            //Checks if distance of i and j is greater => nextParticle, else apply lennardJones
            if (l2Norm > (LinkedCell<LennardJones, dim>::sixthSqrtOfTwo * (*i)->getZeroCrossing()
                * LinkedCell<LennardJones, dim>::sixthSqrtOfTwo * (*i)->getZeroCrossing()))
              continue;

            Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*(*i), *(*j), l2Norm)};

            (*i)->updateForce(force);
            updates.emplace_back(*j, -force);
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
  }

  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, Vector<dim> &gravitation,
                         double current_time) const override {
    LinkedCell<LennardJones, dim>::calculateNextStep(particleContainer, deltaT, gravitation, current_time);
  }
};
