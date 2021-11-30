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
  std::vector<std::unique_ptr<Cell<dim>>> cells{};
  std::vector<Halo<dim>> halosCells;
  std::vector<Halo<dim>> boundaryCells;
  std::vector<Inner<dim>> innerCells;
  std::vector<Halo<dim>> halos;
  std::array<int, dim> cellSize;
  std::array<int, dim> dimension;
  std::vector<BoundaryType> boundaries;

  void setupHalos(size_t type, int cellsPerColumn) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      cells.push_back(std::make_unique<Halo<dim>>(getBoundaries()[type]));
    }
  }

  void setupHalo(size_t type) {
    cells.push_back(std::make_unique<Halo<dim>>(getBoundaries()[type]));
  }

  void setupBoundaries(size_t type, int cellsPerColumn, BoardDirectionType bType) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      cells.push_back(std::make_unique<Boundary<dim>>(getBoundaries()[type], bType));
    }
  }

  void setupBoundary(size_t type, BoardDirectionType bType) {
    cells.push_back(std::make_unique<Boundary<dim>>(getBoundaries()[type], bType));
  }

  void setupInner(int cellsPerColumn) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      cells.push_back(std::make_unique<Inner<dim>>());
    }
  }

  int getIndexBasedOnCoordinates(Vector<dim> coords);

  void insertParticlesInCells() {
    for (Particle<dim> &p: ParticleContainer<dim>::particles) {
      auto &cell = cells[getIndexBasedOnCoordinates(p.getX())];
      cell->insertParticle(&p);
    }
  }

  void setupCells();

  void linkCells();

  size_t countParticleInCells() {
    size_t val = 0;
    for (auto &c: cells) {
      val += c->getParticles().size();
    }
    return val;
  }

 public:
  LinkedCellContainer(std::vector<BoundaryType> pBoundaries, std::array<int, dim> pCellSize,
                      std::array<int, dim> pDimension) : boundaries{std::move(pBoundaries)}, cellSize{pCellSize},
                                                         dimension{pDimension} {
    cells.reserve(static_cast<int>(std::pow(dim + 2, dim)));
  };

  /**
   * Constructs a LinkedCell from the provided vector of particles.
   * @param pParticles vector of particles as initial value.
   */
  LinkedCellContainer(std::vector<Particle<dim>> pParticles, std::array<int, dim> pCellSize,
                      std::array<int, dim> pDimension) : ParticleContainer<dim>(pParticles), dimension{pDimension},
                                                         cellSize{pCellSize} {
    cells.reserve(static_cast<int>(std::pow(dim + 2, dim)));
    SPDLOG_TRACE("LinkedCell generated");
  }

  /**
   * Constructs a LinkedCell from the provided vector of particles.
   * @param pParticles vector of particles as initial value.
   */
  LinkedCellContainer(Vector<dim> pCellSize, Vector<dim> pDimension) : dimension{pDimension}, cellSize{pCellSize} {
    cells.reserve(static_cast<int>(std::pow(dim + 2, dim)));
    SPDLOG_TRACE("LinkedCell generated");
  }

  void init() override {
    setupCells();
    insertParticlesInCells();
    linkCells();
  }

  /**
   * @return Iterator to the beginning of the cell-Vector.
   */
  [[nodiscard]] auto cellBegin() { return cells.begin(); }

  /**
   * @return Iterator to the end of the cell-Vector.
   */
  [[nodiscard]] auto cellEnd() { return cells.end(); }

  [[nodiscard]] const std::vector<BoundaryType> &getBoundaries() const {
    return boundaries;
  }
};