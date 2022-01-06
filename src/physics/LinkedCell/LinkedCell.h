#pragma once

#include "physics/variants/HarmonicPotential.h"
#include "physics/Physics.h"
#include "physics/variants/LennardJones.h"
#include "container/LinkedCell/LinkedCellContainer.h"

/**
 * This class implements the LinkedCell algorithm.
 * @tparam T The physics to be used.
 * @tparam dim The dimension of our simulation
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class LinkedCell : public Physics<T, dim> {
 public:

  //----------------------------------------Methods----------------------------------------

  void performUpdate(ParticleContainer<dim> &particleContainer) const override;

  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, Vector<dim> &,
                         double current_time) const override;
};

/**
 * Implements LinkedCell for LennardJones
 * @tparam dim The dimension of our simulation
 */
template<size_t dim>
class LinkedCell<LennardJones, dim> : public Physics<LennardJones, dim> {
 protected:
  double sixthSqrtOfTwo = std::pow(2, 1.0 / 6.0);

  /**
   * Helper Method to calculate the force between two molecules.
   * @param i Molecule 1
   * @param j Molecule 2
   */
  void inline calculateMoleculeForce(Particle<dim> *i, Particle<dim> *j, double &l2NormSquare) const {
    // TODO Check how expensive
    double l2Norm = std::sqrt(l2NormSquare);
    if (i->isNeighbour(j) || j->isNeighbour(i)) {
      Vector<dim> force{HarmonicPotential::calculateForceBetweenTwoParticles(i, j, l2Norm)};
      i->updateForce(force);
      j->updateForce(-force);
    } else if (i->isDiagonalNeighbour(j) || j->isDiagonalNeighbour(i)) {
      Vector<dim> force{HarmonicPotential::calculateForceBetweenTwoDiagonalParticles(i, j, l2Norm)};
      i->updateForce(force);
      j->updateForce(-force);
    }
  }

  void inline calcBetweenNeighboursAndCell(std::vector<Cell<dim> *> &neighbours,
                                           std::vector<Particle<dim> *> &cellParticles,
                                           LinkedCellContainer<dim> &cellContainer) const {
    // calc between particles in cells and relevant neighbours
    for (auto n = neighbours.begin(); n != neighbours.end(); ++n) {
      for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
        for (auto j = (*n)->getParticles().begin(); j != (*n)->getParticles().end(); ++j) {
          double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*(*i), *(*j));

          if (l2Norm > cellContainer.getCutoffRadiusSquare())
            continue;

          if((*i)->getParticleType() == MOLECULE && (*j)->getParticleType() == MOLECULE && (*i)->getType() == (*j)->getType()) {
            calculateMoleculeForce((*i), (*j), l2Norm);

            //Checks if distance of i and j is greater => nextParticle, else apply lennardJones
            if(l2Norm > (sixthSqrtOfTwo*(*i)->getZeroCrossing() * sixthSqrtOfTwo*(*i)->getZeroCrossing()))
              continue;
          }

          SPDLOG_TRACE("Calculating force for {} and {}", (*i)->toString(), (*j)->toString());
          Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*(*i), *(*j), l2Norm)};
          (*i)->updateForce(force);
          (*j)->updateForce(-force);
        }
      }
    }
  }

  void inline calcInTheCell(std::vector<Particle<dim> *> &cellParticles) const {
    // calc in the cells
    for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
      for (auto j = i + 1; j != cellParticles.end(); ++j) {
        SPDLOG_TRACE("Calculating force for {} and {}", (*i)->toString(), (*j)->toString());

        double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(*(*i), *(*j));

        if((*i)->getParticleType() == MOLECULE && (*j)->getParticleType() == MOLECULE && (*i)->getType() == (*j)->getType()) {
          calculateMoleculeForce((*i), (*j), l2Norm);

          //Checks if distance of i and j is greater => nextParticle, else apply lennardJones
          if (l2Norm > (sixthSqrtOfTwo * (*i)->getZeroCrossing() * sixthSqrtOfTwo * (*i)->getZeroCrossing()))
            continue;
        }

        Vector<dim> force{LennardJones::calculateForceBetweenTwoParticles<dim>(*(*i), *(*j), l2Norm)};

        (*i)->updateForce(force);
        (*j)->updateForce(-force);
      }
    }
  }

  void inline calcPeriodic(std::vector<Particle<dim> *> &cellParticles, LinkedCellContainer<dim> &cellContainer,
                           Cell<dim> &cell) const {
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

            if((*i)->getParticleType() == MOLECULE && (*j)->getParticleType() == MOLECULE && (*i)->getType() == (*j)->getType()) {
              calculateMoleculeForce((*i), (*j), l2Norm);

              //Checks if distance of i and j is greater => nextParticle, else apply lennardJones
              if(l2Norm > (sixthSqrtOfTwo*(*i)->getZeroCrossing() * sixthSqrtOfTwo*(*i)->getZeroCrossing()))
                continue;
            }

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
 public:

  //----------------------------------------Methods----------------------------------------

  void performUpdate(ParticleContainer<dim> &particleContainer) const override {
    auto &cellContainer = static_cast<LinkedCellContainer<dim> &>(particleContainer);
    for (Boundary<dim> &b: cellContainer.getBoundaryCells()) {
      b.applyCellProperties();
    }

    for (size_t c = 0; c < cellContainer.getBoundaryAndInnerCells().size(); ++c) {

      Cell<dim> *cell = cellContainer.getBoundaryAndInnerCells()[c];
      std::vector<Cell<dim> *> &neighbours = cell->getNeighbours();
      std::vector<Particle<dim> *> &cellParticles = cell->getParticles();

      if (!cellParticles.empty()) {

        calcBetweenNeighboursAndCell(neighbours, cellParticles, cellContainer);

        calcInTheCell(cellParticles);

        calcPeriodic(cellParticles, cellContainer, *cell);
      }
    }
  }

  /**
   * Calls the calculate-Methods for the position, force and velocity with the given parameters.
   * @param particleContainer The ParticleContainer, for whose contents the positions should be calculated.
   * @param deltaT time step of our simulation
  */
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, Vector<dim> &gravitation,
                         double current_time) const override {
    // Calculate new x
    Physics<LennardJones, dim>::calculateX(particleContainer, deltaT);

    // Update cells
    particleContainer.updateCells();

    auto &cellContainer = static_cast<LinkedCellContainer<dim> &>(particleContainer);

    // Apply Halo properties
//#pragma omp parallel for shared(cellContainer) default(none)
    for (size_t i = 0; i < cellContainer.getHalosCells().size(); ++i) {
      Halo<dim> &h = cellContainer.getHalosCells()[i];
      h.applyCellProperties();
    }

    // Calculate new f
    Physics<LennardJones, dim>::calculateF(particleContainer, gravitation, current_time);

    // Calculate new v
    Physics<LennardJones, dim>::calculateV(particleContainer, deltaT);

    // Delete all deleted Particle
    std::vector<Particle<dim>> &particles = particleContainer.getParticles();
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](auto &p) {
      return p.getType() == -1;
    }), particles.end());
  }
};
