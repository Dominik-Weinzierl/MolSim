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
 * @tparam dim dimension of our simulation
 */
template<size_t dim>
class LinkedCellContainer : public ParticleContainer<dim> {
 private:
  /**
   * Precision we use to build our mesh, as we want to avoid holes.
   */
  const double precision = 0.01;

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
  const Vector<dim> cellSize;

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
  const Vector<dim> domain;

  /**
   * Boundary type of each side (4/6).
   */
  std::vector<BoundaryType> boundaries;

  //----------------------------------------Methods----------------------------------------

  /**
   * Setup Halo(s) where needed.
   * @param amount amount of Halo(s)
   * @param pBorderDirection the direction of the Halo(s)
   * @param position the start position of these Halo(s)
   */
  void setupHalos(int amount, std::vector<BoardDirectionType> pBorderDirection, Vector<dim> position) {
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
  void setupHalo(std::vector<BoardDirectionType> pBorderDirection, Vector<dim> position) {
    std::vector<BoundaryType> boundaryTypes{};
    // Outflow
    for (BoardDirectionType &b: pBorderDirection) {
      BoundaryType temp = getBoundaries()[b];
      if (temp == BoundaryType::Outflow) {
        boundaryTypes = {BoundaryType::Outflow};
        break;
      }
      boundaryTypes.push_back(getBoundaries()[b]);
    }

    // Periodic
    if (std::all_of(boundaryTypes.cbegin(), boundaryTypes.cend(), [](auto &b) {
      return b == BoundaryType::Periodic;
    })) {
      boundaryTypes = {BoundaryType::Periodic};
    }

    halosCells.emplace_back(boundaryTypes, pBorderDirection, position, cellSize, domain);
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
  void setupBoundaries(int amount, std::vector<BoardDirectionType> pBorderDirection, Vector<dim> position) {
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
  void setupBoundary(std::vector<BoardDirectionType> pBorderDirection, Vector<dim> position) {
    std::vector<BoundaryType> boundaryTypes{};
    for (BoardDirectionType &b: pBorderDirection) {
      boundaryTypes.push_back(getBoundaries()[b]);
    }
    boundaryCells.emplace_back(boundaryTypes, pBorderDirection, position, cellSize, domain);
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
  void setupInner(int amount, Vector<dim> position) {
    for (int y = 0; y < amount; ++y) {
      innerCells.emplace_back(position, cellSize, domain);
      auto *ptr = &innerCells[innerCells.size() - 1];
      cells.push_back(ptr);
      boundaryAndInnerCells.push_back(ptr);
      position[1] += cellSize[1];
    }
  }

  //----------------------------------------Linking methods----------------------------------------

  /**
   * Link Cell structure.
   */
  void linkCells();

  /**
   * Link Halo cells to support periodic boundaries.
   */
  void linkHalosForPeriodic();

  //----------------------------------------Particle operations----------------------------------------


  /**
   * Insert a pointer to the Particle into the correct Cell.
   */
  void insertParticlesInCells() {
    for (Particle<dim> &p: ParticleContainer<dim>::particles) {
      if (p.getType() != -1) {
        auto index = static_cast<size_t>(getIndexBasedOnCoordinates(p.getX()));
        if (index >= cells.size()) {
          SPDLOG_ERROR("Particle got out of bounds [{}]! Please check your configuration", index);
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
   * Reserve enough space in vectors to avoid reference issues.
   */
  void reserve();

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * Constructor for LinkedCellContainer.
   * @param pBoundaries user defined boundaries on all sides
   * @param pCellSize cell size used during this simulation
   * @param pDomain domain size used during this simulation
   * @param pCutoffRadius cutoff radius is used to define the range of our force
   */
  LinkedCellContainer(std::vector<BoundaryType> pBoundaries, Vector<dim> pCellSize, Vector<dim> pDomain,
                      double pCutoffRadius) : boundaries{std::move(pBoundaries)}, cellSize{pCellSize}, domain{pDomain},
                                              cutoffRadius{pCutoffRadius},
                                              cutoffRadiusSquare{pCutoffRadius * pCutoffRadius} {
    reserve();
    SPDLOG_TRACE("LinkedCellContainer generated");
  };

  //----------------------------------------Methods----------------------------------------

  /**
   * Setup linked cell structure.
   */
  void init() override {
    SPDLOG_TRACE("LinkedCellContainer->init(): Init structure");
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
    SPDLOG_TRACE("LinkedCellContainer->updateCells(): Clear cells and insert particles {}", this->particles.size());
    for (auto *c: cells) {
      c->getParticles().clear();
    }
    insertParticlesInCells();
  }

  /**
   * Set the precision for this double (round up and down)
   * @param value which needs to be adapted
   */
  double setDoublePrecision(double value) {
    return std::floor(value / precision + 0.5) * precision;
  }

  /**
   * Helper function to calculate the amount of Cell(s) per column.
   * @return amount of Cell(s) per column as int
   */
  int cellsPerColumn() {
    double amount = setDoublePrecision(domain[1] / cellSize[1]);
    return static_cast<int>(amount);
  }

  /**
   * Helper function to calculate the amount of Cell(s) per row.
   * @return amount of Cell(s) per row as int
   */
  int cellsPerRow() {
    double amount = setDoublePrecision(domain[0] / cellSize[0]);
    return static_cast<int>(amount);
  }

  /**
   * Helper function to calculate the amount of Cell(s) per depth.
   * @return amount of Cell(s) per depth as int
   */
  int cellsPerDepth() {
    double amount = setDoublePrecision(domain[2] / cellSize[2]);
    return static_cast<int>(amount);
  }

  //----------------------------------------Getter & Setter----------------------------------------

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
   * Getter for cutoffRadius(s).
   * @return cutoffRadius
   */
  [[nodiscard]] const Vector<dim> &getCellSize() const {
    return cellSize;
  }

  /**
   * Getter for domain.
   * @return domain
   */
  [[nodiscard]] const Vector<dim> &getDomain() const {
    return domain;
  }

  /**
   * Getter for boundary and inner cells.
   * @return boundaryAndInnerCells
   */
  [[nodiscard]] const std::vector<Cell<dim> *> &getBoundaryAndInnerCells() const {
    return boundaryAndInnerCells;
  }

  /**
   * Getter for inner cells.
   * @return boundaryAndInnerCells
   */
  [[nodiscard]] const std::vector<Inner<dim>> &getInnerCells() const {
    return innerCells;
  }

  /**
   * Getter for all cells.
   * @return cells
   */
  [[nodiscard]] const std::vector<Cell<dim> *> &getCells() const {
    return cells;
  }
};
