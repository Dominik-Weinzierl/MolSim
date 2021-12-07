#pragma once

#include "Physics.h"
#include "physics/variants/LennardJones.h"
#include "container/LinkedCell/LinkedCellContainer.h"

/**
 * This class implements the LinkedCell algorithm.
 * @tparam T The physics to be used.
 * @tparam dim The dimension of our simulation
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class LinkedCell : public Physics<T, dim> {
  void performUpdate(ParticleContainer<dim> &particleContainer) const override;
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT) const override;
};

/**
 * Implements LinkedCell for LennardJones
 * @tparam dim The dimension of our simulation
 */
template<size_t dim>
class LinkedCell<LennardJones, dim> : public Physics<LennardJones, dim> {
 private:
 public:
  void performUpdate(ParticleContainer<dim> &particleContainer) const override {
    auto &cellContainer = static_cast<LinkedCellContainer<dim> &>(particleContainer);
    for (Boundary<dim> &b: cellContainer.getBoundaryCells()) {
      b.applyCellProperties();
    }

    for (auto cell = cellContainer.cellBegin(); cell != cellContainer.cellEnd(); ++cell) {
      std::vector<Cell<dim> *> &neighbours = (*cell)->getNeighbours();
      std::vector<Particle<dim> *> &cellParticles = (*cell)->getParticles();

      // calc between particles in cells and relevant neighbours
      for (auto n = neighbours.begin(); n != neighbours.end(); ++n) {
        for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
          for (auto j = (*n)->getParticles().begin(); j != (*n)->getParticles().end(); ++j) {
            double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*(*i), *(*j));

            if (l2Norm > cellContainer.getCutoffRadiusSquare())
              continue;

            SPDLOG_TRACE("Calculating force for {} and {}", (*(*i))->toString(), (*(*j))->toString());
            Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*(*i), *(*j), l2Norm)};
            (*i)->updateForce(force);
            (*j)->updateForce(-force);
          }
        }
      }

      // calc in the cells
      for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
        for (auto j = i + 1; j != cellParticles.end(); ++j) {
          SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());

          double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*(*i), *(*j));

          Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*(*i), *(*j), l2Norm)};

          (*i)->updateForce(force);
          (*j)->updateForce(-force);
        }
      }
    }
  }

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
  */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT) const override {
    // calculate new x
    Physics<LennardJones, dim>::calculateX(particleContainer, deltaT);

    // Update cells
    particleContainer.updateCells();

    // calculate new f
    Physics<LennardJones, dim>::calculateF(particleContainer);

    // calculate new v
    Physics<LennardJones, dim>::calculateV(particleContainer, deltaT);

    auto &cellContainer = static_cast<LinkedCellContainer<dim> &>(particleContainer);

    // Apply Halo properties
    for (Halo<dim> &h: cellContainer.getHalosCells()) {
      h.applyCellProperties();
    }

    // Delete all deleted Particle
    std::vector<Particle<dim>> &particles = particleContainer.getParticles();
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](auto &p) {
      return p.getType() == -1;
    }), particles.end());

  }
};
