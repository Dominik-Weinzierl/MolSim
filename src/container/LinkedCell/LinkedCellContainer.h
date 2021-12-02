#pragma once

#include "container/ParticleContainer.h"
#include "container/Cell/Cell.h"
#include <utility>
#include <vector>
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
   * Domain of our simulation.
   */
  const std::array<int, dim> domain;

  /**
   * Boundary type of each side (4/6)
   */
  std::vector<BoundaryType> boundaries;

  void setupHalos(int amount, std::vector<BoardDirectionType> pBorderDirection, std::array<int, dim> position) {
    for (int y = 0; y < amount; ++y) {
      setupHalo(pBorderDirection, position);
      position[1] += cellSize[1];
    }
  }

  void setupHalo(std::vector<BoardDirectionType> pBorderDirection, std::array<int, dim> position) {
    /**
     * Currently we have only particles in our Halo-Cell, if the mesh side is outflow.
     */
    /*std::vector<BoundaryType> boundaryTypes{};
    for (BoardDirectionType &b: pBorderDirection) {
      boundaryTypes.push_back(getBoundaries()[b]);
    }*/
    halosCells
        .emplace_back(std::vector<BoundaryType>{BoundaryType::Outflow}, pBorderDirection, this->particles, position,
                      cellSize);
    cells.push_back(&halosCells[halosCells.size() - 1]);
  }

  void setupBoundaries(int amount, std::vector<BoardDirectionType> pBorderDirection, std::array<int, dim> position) {
    for (int y = 0; y < amount; ++y) {
      setupBoundary(pBorderDirection, position);
      position[1] += cellSize[1];
    }
  }

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

  void setupInner(int amount, std::array<int, dim> position) {
    for (int y = 0; y < amount; ++y) {
      innerCells.emplace_back(this->particles, position, cellSize);
      auto *ptr = &innerCells[innerCells.size() - 1];
      cells.push_back(ptr);
      boundaryAndInnerCells.push_back(ptr);
      position[1] += cellSize[1];
    }
  }

  int getIndexBasedOnCoordinates(Vector<dim> coords);

  void insertParticlesInCells() {
    for (Particle<dim> &p: ParticleContainer<dim>::particles) {
      if (p.getType() != -1) {
        auto *cell = cells[static_cast<unsigned long>(getIndexBasedOnCoordinates(p.getX()))];
        cell->insertParticle(&p);
      }
    }
  }

  void setupCells();

  void linkCells();

  size_t countParticleInCells() {
    size_t val = 0;
    for (auto *c: cells) {
      val += c->getParticles().size();
    }
    return val;
  }

  void reserve();

 public:
  LinkedCellContainer(std::vector<BoundaryType> pBoundaries, std::array<int, dim> pCellSize,
                      std::array<int, dim> pDomain, double pCutoffRadius) : boundaries{std::move(pBoundaries)},
                                                                            cellSize{pCellSize}, domain{pDomain},
                                                                            cutoffRadius{pCutoffRadius} {
    reserve();
  };

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
   * @return Iterator to the beginning of the cell-Vector.
   */
  [[nodiscard]] auto cellBegin() { return boundaryAndInnerCells.begin(); }

  /**
   * @return Iterator to the end of the cell-Vector.
   */
  [[nodiscard]] auto cellEnd() { return boundaryAndInnerCells.end(); }

  [[nodiscard]] const std::vector<BoundaryType> &getBoundaries() const {
    return boundaries;
  }

  [[nodiscard]] std::vector<Halo<dim>> &getHalosCells() {
    return halosCells;
  }

  [[nodiscard]] std::vector<Boundary<dim>> &getBoundaryCells() {
    return boundaryCells;
  }

};