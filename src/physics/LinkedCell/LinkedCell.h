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
  void calculateNextStep(ParticleContainer<dim> &particleContainer, double deltaT, Vector<dim> &gravitation,
                         double current_time) const override;
};

/**
 * Implements LinkedCell for LennardJones
 * @tparam dim The dimension of our simulation
 */
template<size_t dim>
class LinkedCell<LennardJones, dim> : public Physics<LennardJones, dim> {
 protected:
  /**
   * Used to truncate the repulsive part of lennard jones for molecules.
   */
  double sixthSqrtOfTwo = std::pow(2, 1.0 / 6.0);

  /**
   * This method calculates the Lennard-Jones potential between two particles.
   * First we check whether the calculation is valid, otherwise we abort at an early stage.
   * @param i first Particle
   * @param j second Particle
   * @param cellContainer that provides possible required values and functionalities
   */
  inline Vector<dim> calculateLennardJones(Particle<dim> &i, Particle<dim> &j,
                                           LinkedCellContainer<dim> &cellContainer) const {
    double l2Norm = Physics<LennardJones, dim>::calcL2NormSquare(i, j);

    // This prevents molecules from attracting each other too strongly due to the Lennard Jones potential.
    // Therefore, the force is only effective when the molecules are close enough to each other.
    if (i.getParticleType() == MOLECULE && j.getParticleType() == MOLECULE && i.getType() == j.getType()) {

      // Checks if distance of i and j is greater => nextParticle, else apply lennardJones
      if (l2Norm > (sixthSqrtOfTwo * i.getZeroCrossing() * sixthSqrtOfTwo * j.getZeroCrossing()))
        return Vector<dim>{};
    }

    if (l2Norm > cellContainer.getCutoffRadiusSquare())
      return Vector<dim>{};

    SPDLOG_TRACE("Calculating force for {} and {}", (*i)->toString(), (*j)->toString());
    return LennardJones::calculateForceBetweenTwoParticles<dim>(i, j, l2Norm);
  }

  /**
   * This method updates the force for two particles.
   * @param i first Particle
   * @param j second Particle
   * @param force additional force
   */
  inline void updateForceForParticle(Particle<dim> &i, Particle<dim> &j, Vector<dim> &force) const {
    if (!isNull(force)) {
      i.updateForce(force);
      j.updateForce(-force);
    }
  }

  /**
   * This method calculates the harmonic potential between two molecules depending on how they are related.
   * A parallel or diagonal relationship is possible.
   * @param cellContainer that provides a list of molecules
   */
  void inline calculateMolecules(LinkedCellContainer<dim> &cellContainer) const {
    // Iteration over all molecules
    for (Particle<dim> *p: cellContainer.getMolecules()) {
      // Molecules which aren't diagonal
      for (Particle<dim> *n: p->getNeighbours()) {
        double l2Norm = std::sqrt(Physics<LennardJones, dim>::calcL2NormSquare(*p, *n));
        Vector<dim> force{HarmonicPotential::calculateForceBetweenTwoParticles(p, n, l2Norm)};
        updateForceForParticle(*p, *n, force);
      }
      // Molecules which are diagonal
      for (Particle<dim> *d: p->getDiagonalNeighbours()) {
        double l2Norm = std::sqrt(Physics<LennardJones, dim>::calcL2NormSquare(*p, *d));
        Vector<dim> force{HarmonicPotential::calculateForceBetweenTwoDiagonalParticles(p, d, l2Norm)};
        updateForceForParticle(*p, *d, force);
      }
    }
  }

  /**
   * This method calculates the forces between particles in different cells.
   * Only those cells are considered that are also related to each other (neighbours).
   * @param neighbours vector of cells that are related to the cell
   * @param cellParticles Particle(s) in the current cell
   * @param cellContainer that provides possible required values and functionalities
   */
  void inline calcBetweenNeighboursAndCell(std::vector<Cell<dim> *> &neighbours,
                                           std::vector<Particle<dim> *> &cellParticles,
                                           LinkedCellContainer<dim> &cellContainer) const {
    // calc between particles in cells and relevant neighbours
    for (auto n = neighbours.begin(); n != neighbours.end(); ++n) {
      for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
        for (auto j = (*n)->getParticles().begin(); j != (*n)->getParticles().end(); ++j) {
          auto force = calculateLennardJones(*(*i), *(*j), cellContainer);
          updateForceForParticle(*(*i), *(*j), force);
        }
      }
    }
  }

  /**
   * In this method we calculate the forces between all particles in the current cell.
   * The cutoff radius may be smaller than the cell size, so it must still be considered.
   * @param cellParticles Particle(s) in the current cell
   * @param cellContainer that provides possible required values and functionalities
   */
  void inline calcInTheCell(std::vector<Particle<dim> *> &cellParticles,
                            LinkedCellContainer<dim> &cellContainer) const {
    // calc in the cells
    for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
      for (auto j = i + 1; j != cellParticles.end(); ++j) {
        auto force = calculateLennardJones(*(*i), *(*j), cellContainer);
        updateForceForParticle(*(*i), *(*j), force);
      }
    }
  }

  /**
   * This method deals with the special case that forces also act around the boundaries.
   * @param cellParticles Particle(s) in the current cell
   * @param cellContainer that provides possible required values and functionalities
   * @param cell which has periodic influence
   */
  void inline calcPeriodic(std::vector<Particle<dim> *> &cellParticles, LinkedCellContainer<dim> &cellContainer,
                           Cell<dim> &cell) const {
    std::vector<std::tuple<Cell<dim> *, Vector<dim>>> &periodicNeighbours = cell.getPeriodicNeighbours();

    // Iterate over all periodic neighbours
    for (std::tuple<Cell<dim> *, Vector<dim>> &t: periodicNeighbours) {
      // Get the periodic cell which influences the current cell
      Cell<dim> *periodicCell = std::get<0>(t);

      if (!periodicCell->getParticles().empty()) {

        for (auto j = periodicCell->getParticles().begin(); j != periodicCell->getParticles().end(); ++j) {
          // Update the current position of the Particle(s)
          const Vector<dim> oldPos = (*j)->getX();
          Vector<dim> pos;
          for (size_t index = 0; index < dim; ++index) {
            pos[index] = oldPos[index] - periodicCell->getPosition()[index] + std::get<1>(t)[index];
          }
          (*j)->setX(pos);

          for (auto i = cellParticles.begin(); i != cellParticles.end(); ++i) {
            auto force = calculateLennardJones(*(*i), *(*j), cellContainer);
            updateForceForParticle(*(*i), *(*j), force);
          }

          (*j)->setX(oldPos);
        }
      }
    }
  }
 public:

  //----------------------------------------Methods----------------------------------------

  /**
   * This method calculates the forces between the different particles in the different cells.
   * @param particleContainer that provides possible required values and functionalities
   */
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

        calcInTheCell(cellParticles, cellContainer);

        calcPeriodic(cellParticles, cellContainer, *cell);
      }
    }

    calculateMolecules(cellContainer);
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
