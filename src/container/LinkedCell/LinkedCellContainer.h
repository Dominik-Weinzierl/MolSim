#pragma once

#include <utility>
#include <vector>

#include "container/ParticleContainer.h"
#include "container/Cell/Cell.h"
#include "container/Cell/variants/Halo.h"
#include "container/Cell/variants/Boundary.h"
#include "container/Cell/variants/Inner.h"

/**
 * LinkedCell is a container used to perform calculations based on the linked cell algorithm.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class LinkedCellContainer : public ParticleContainer<dim> {
 private:
  /**
   * All cells created and used by this LinkedCellContainer.
   */
  std::vector<Cell<dim> *> cells;

  /**
   * Cells which are relevant for force calculations.
   */
  std::vector<Cell<dim> *> boundaryAndInnerCells;

  /**
   * Halo(s) are the outermost cells. Used to delete Particle(s) or perform additional periodic operations.
   */
  std::vector<Halo<dim>> halosCells;

  /**
   * Boundary(s) are the outermost cells inside of the domain. Used to keep Particle(s) inside the domain if needed.
   */
  std::vector<Boundary<dim>> boundaryCells;

  /**
   * Inner(s) are the innermost cells which have no additional tasks.
   */
  std::vector<Inner<dim>> innerCells;

  /**
   * Cell size of each Cell. This is fixed and won't change during the simulation.
   */
  const std::array<int, dim> cellSize;

  /**
   * Cutoff radius used by the linked cell algorithm to optimize calculations.
   */
  const double cutoffRadius;

  /**
   * Cutoff radius used by the linked cell algorithm to optimize calculations.
   */
  const double cutoffRadiusSquare;

  /**
   * Domain of our simulation.
   */
  const std::array<int, dim> domain;

  /**
   * Boundary type of each side (4/6)
   */
  std::vector<BoundaryType> boundaries;

  /**
   * Setup Halo(s) where needed.
   * @param amount amount of Halo(s)
   * @param pBorderDirection the direction of the Halo(s)
   * @param position the start position of these Halo(s)
   */
  void setupHalos(int amount, std::vector<BoardDirectionType> pBorderDirection, std::array<int, dim> position) {
    for (int y = 0; y < amount; ++y) {
      setupHalo(pBorderDirection, position);
      position[1] += cellSize[1];
    }
  }

  /**
   * Setup a single Halo.
   * @param pBorderDirection the direction of the Halo
   * @param position the start position of this Halo
   */
  void setupHalo(std::vector<BoardDirectionType> pBorderDirection, std::array<int, dim> position) {
    std::vector<BoundaryType> boundaryTypes{};
    for (BoardDirectionType &b: pBorderDirection) {
      BoundaryType temp = getBoundaries()[b];
      if (temp == BoundaryType::Outflow) {
        boundaryTypes = {BoundaryType::Outflow};
        break;
      }
      boundaryTypes.push_back(getBoundaries()[b]);
    }
    halosCells.emplace_back(boundaryTypes, pBorderDirection, this->particles, position, cellSize);
    cells.push_back(&halosCells[halosCells.size() - 1]);
  }

  /**
   * Creates Halo column to decrease code duplicates.
   * @param cellsPerColumn cells per column
   * @param cellsPerRow cells per row
   * @param pos position of this layer
   * @param d describes the position of this row
   */
  inline void setupHaloColumnsWrapper(int cellsPerColumn, int cellsPerRow, std::array<int, 2> pos,
                                      BoardDirectionType d);

  /**
   * Creates Halo column to decrease code duplicates.
   * @param cellsPerColumn cells per column
   * @param pos position of this layer
   * @param d describes the position of this row
   */
  inline void setupHaloColumnWrapper(int cellsPerColumn, std::array<int, 2> pos, BoardDirectionType d);

  /**
   * Setup Boundary(s) where needed.
   * @param amount amount of Boundary(s)
   * @param pBorderDirection the direction of the Boundary(s)
   * @param position the start position of these Boundary(s)
   */
  void setupBoundaries(int amount, std::vector<BoardDirectionType> pBorderDirection, std::array<int, dim> position) {
    for (int y = 0; y < amount; ++y) {
      setupBoundary(pBorderDirection, position);
      position[1] += cellSize[1];
    }
  }

  /**
   * Setup a single Boundary.
   * @param pBorderDirection the direction of the Boundary
   * @param position the start position of this Boundary
   */
  void setupBoundary(std::vector<BoardDirectionType> pBorderDirection, std::array<int, dim> position) {
    std::vector<BoundaryType> boundaryTypes{};
    for (BoardDirectionType &b: pBorderDirection) {
      boundaryTypes.push_back(getBoundaries()[b]);
    }
    boundaryCells.emplace_back(boundaryTypes, pBorderDirection, this->particles, position, cellSize);
    auto *ptr = &boundaryCells[boundaryCells.size() - 1];
    cells.push_back(ptr);
    boundaryAndInnerCells.push_back(ptr);
  }

  /**
   * Creates Boundary column to decrease code duplicates.
   * @param cellsPerColumn cells per column
   * @param cellsPerRow cells per row
   * @param pos position of this layer
   * @param d describes the position of this row
   */
  inline void setupBoundaryColumnsWrapper(int cellsPerColumn, int cellsPerRow, std::array<int, 2> pos,
                                          BoardDirectionType d);

  /**
   * Creates Boundary column to decrease code duplicates.
   * @param cellsPerColumn cells per column
   * @param pos position of this layer
   * @param d describes the position of this row
   */
  inline void setupBoundaryColumnWrapper(int cellsPerColumn, std::array<int, 2> pos, BoardDirectionType d);
  /**
   * Setup Inner(s).
   * @param amount amount of Inner(s)
   * @param position the start position of these Inner(s)
   */
  void setupInner(int amount, std::array<int, dim> position) {
    for (int y = 0; y < amount; ++y) {
      innerCells.emplace_back(this->particles, position, cellSize);
      auto *ptr = &innerCells[innerCells.size() - 1];
      cells.push_back(ptr);
      boundaryAndInnerCells.push_back(ptr);
      position[1] += cellSize[1];
    }
  }

  /**
   * Insert a pointer to the Particle into the correct Cell.
   */
  void insertParticlesInCells() {
    for (Particle<dim> &p: ParticleContainer<dim>::particles) {
      if (p.getType() != -1) {
        size_t index = getIndexBasedOnCoordinates(p.getX());
        if (index >= cells.size()) {
          throw std::invalid_argument("Particle got out of bounds! Please check your configuration");
        }
        auto *cell = cells[index];
        cell->insertParticle(&p);
      }
    }
  }

  /**
   * Setup Cell structure.
   */
  void setupCells();

  /**
   * Link Cell structure.
   */
  void linkCells();

  /**
   * Reserve enough space in vectors tro avoid reference issues.
   */
  void reserve();

 public:
  /**
   * Constructor for LinkedCellContainer.
   * @param pBoundaries user defined boundaries on all sides
   * @param pCellSize cell size used during this simulation
   * @param pDomain domain size used during this simulation
   * @param pCutoffRadius cutoff radius is used to define the range of our force
   */
  LinkedCellContainer(std::vector<BoundaryType> pBoundaries, std::array<int, dim> pCellSize,
                      std::array<int, dim> pDomain, double pCutoffRadius) : boundaries{std::move(pBoundaries)},
                                                                            cellSize{pCellSize}, domain{pDomain},
                                                                            cutoffRadius{pCutoffRadius},
                                                                            cutoffRadiusSquare{
                                                                                pCutoffRadius * pCutoffRadius} {
    reserve();
  };

  /**
   * Setup linked cell structure.
   */
  void init() override {
    cells.clear();
    boundaryAndInnerCells.clear();

    halosCells.clear();
    boundaryCells.clear();
    innerCells.clear();

    setupCells();
    insertParticlesInCells();
    linkCells();
  }

  /**
  * Used to calculate the index of the Cell in our cell list.
  * @param coords position of the Particle
  * @return list index
  */
  int getIndexBasedOnCoordinates(Vector<dim> coords);

  void updateCells() override {
    for (auto *c: cells) {
      c->getParticles().clear();
    }
    insertParticlesInCells();
  }

  /**
   * @return Iterator to the beginning of the cell-Vector.
   */
  [[nodiscard]] auto cellBegin() { return boundaryAndInnerCells.begin(); }

  /**
   * @return Iterator to the end of the cell-Vector.
   */
  [[nodiscard]] auto cellEnd() { return boundaryAndInnerCells.end(); }

  /**
   * Getter for boundaries.
   * @return boundaries
   */
  [[nodiscard]] const std::vector<BoundaryType> &getBoundaries() const {
    return boundaries;
  }

  /**
   * Getter for Halo(s).
   * @return std::vector<Halo<dim>> halosCells
   */
  [[nodiscard]] std::vector<Halo<dim>> &getHalosCells() {
    return halosCells;
  }

  /**
   * Getter for Boundary(s).
   * @return std::vector<Boundary<dim>> boundaryCells
   */
  [[nodiscard]] std::vector<Boundary<dim>> &getBoundaryCells() {
    return boundaryCells;
  }

  /**
   * Getter for cutoffRadius(s).
   * @return cutoffRadius
   */
  [[nodiscard]] const double &getCutoffRadius() const {
    return cutoffRadius;
  }

  /**
   * Getter for cutoffRadiusSquare(s).
   * @return cutoffRadiusSquare
   */
  [[nodiscard]] const double &getCutoffRadiusSquare() const {
    return cutoffRadiusSquare;
  }

  /**
   * Getter for domain.
   * @return domain
   */
  [[nodiscard]] const std::array<int, dim> &getDomain() const {
    return domain;
  }

  /**
   * Getter for boundary and inner cells.
   * @return boundaryAndInnerCells
   */
  [[nodiscard]] std::vector<Cell<dim> *> getBoundaryAndInnerCells() const {
    return boundaryAndInnerCells;
  }

};