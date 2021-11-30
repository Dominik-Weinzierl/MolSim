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
  std::vector<Cell<dim> *> cells;
  std::vector<Cell<dim> *> boundaryAndInnerCells;

  std::vector<Halo<dim>> halosCells;
  std::vector<Boundary<dim>> boundaryCells;
  std::vector<Inner<dim>> innerCells;

  std::array<int, dim> cellSize;
  std::array<int, dim> dimension;
  std::vector<BoundaryType> boundaries;

  void setupHalos(size_t type, int cellsPerColumn, std::array<int, dim> position) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      position[0] = y * cellSize[1];
      halosCells.emplace_back(getBoundaries()[type], position, cellSize);
      cells.push_back(&halosCells[halosCells.size() - 1]);
    }
  }

  void setupHalo(size_t type, std::array<int, dim> position) {
    halosCells.emplace_back(getBoundaries()[type], position, cellSize);
    cells.push_back(&halosCells[halosCells.size() - 1]);
  }

  void setupBoundaries(size_t type, int cellsPerColumn, BoardDirectionType bType, std::array<int, dim> position) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      position[1] = (y + 1) * cellSize[1];
      boundaryCells.emplace_back(getBoundaries()[type], bType, position, cellSize);
      auto *ptr = &boundaryCells[boundaryCells.size() - 1];
      cells.push_back(ptr);
      boundaryAndInnerCells.push_back(ptr);
    }
  }

  void setupBoundary(size_t type, BoardDirectionType bType, std::array<int, dim> position) {
    boundaryCells.emplace_back(getBoundaries()[type], bType, position, cellSize);
    auto *ptr = &boundaryCells[boundaryCells.size() - 1];
    cells.push_back(ptr);
    boundaryAndInnerCells.push_back(ptr);
  }

  void setupInner(int cellsPerColumn, std::array<int, dim> position) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      position[1] = (y + 2) * cellSize[1];
      innerCells.emplace_back(position, cellSize);
      auto *ptr = &innerCells[innerCells.size() - 1];
      cells.push_back(ptr);
      boundaryAndInnerCells.push_back(ptr);
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
                      std::array<int, dim> pDimension) : boundaries{std::move(pBoundaries)}, cellSize{pCellSize},
                                                         dimension{pDimension} {
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
};