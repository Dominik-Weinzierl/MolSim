#include <cmath>

#include "LinkedCellContainer.h"

template<>
void LinkedCellContainer<3>::setupHaloColumnWrapper(int cellsPerColumn, std::array<int, 2> pos, BoardDirectionType d) {
  /**
   *  Setup a Halo column from Bottom (B) to Top (T)
   *  T - - - -
   *  x - - - -
   *  x - - - -
   *  x - - - -
   *  B - - - -
   */
  setupHalo({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], -cellSize[1], pos[1] * cellSize[2]});
  setupHalos(cellsPerColumn - 2, {d}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
  setupHalo({d, BoardDirectionType::TOP},
            {pos[0] * cellSize[0], (cellsPerColumn - 2) * cellSize[1], pos[1] * cellSize[2]});
}

template<>
void LinkedCellContainer<2>::setupHaloColumnWrapper(int cellsPerColumn, std::array<int, 2> pos, BoardDirectionType d) {
  /**
   *  Setup a Halo column from Bottom (B) to Top (T)
   *  T - - - -
   *  x - - - -
   *  x - - - -
   *  x - - - -
   *  B - - - -
   */
  setupHalo({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], -cellSize[1]});
  setupHalos(cellsPerColumn - 2, {d}, {pos[0] * cellSize[0], 0});
  setupHalo({d, BoardDirectionType::TOP}, {pos[0] * cellSize[0], (cellsPerColumn - 2) * cellSize[1]});
}

template<>
void LinkedCellContainer<3>::setupHaloColumnsWrapper(int cellsPerColumn, int cellsPerRow, std::array<int, 2> pos,
                                                     BoardDirectionType d) {
  if (pos[0] == -1) {
    setupHalo({BoardDirectionType::LEFT, d, BoardDirectionType::BOTTOM},
              {pos[0] * cellSize[0], -cellSize[1], pos[1] * cellSize[2]});
    setupHalos(cellsPerColumn - 2, {BoardDirectionType::LEFT, d}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
    setupHalo({BoardDirectionType::LEFT, d, BoardDirectionType::TOP},
              {pos[0] * cellSize[0], (cellsPerColumn - 2) * cellSize[1], pos[1] * cellSize[2]});
  } else if (pos[0] == cellsPerRow - 2) {
    setupHalo({BoardDirectionType::RIGHT, d, BoardDirectionType::BOTTOM},
              {pos[0] * cellSize[0], -cellSize[1], pos[1] * cellSize[2]});
    setupHalos(cellsPerColumn - 2, {BoardDirectionType::RIGHT, d}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
    setupHalo({BoardDirectionType::RIGHT, d, BoardDirectionType::TOP},
              {pos[0] * cellSize[0], (cellsPerColumn - 2) * cellSize[1], pos[1] * cellSize[2]});
  } else {
    setupHaloColumnWrapper(cellsPerColumn, pos, d);
  }
}

template<>
void LinkedCellContainer<3>::setupBoundaryColumnWrapper(int cellsPerColumn, std::array<int, 2> pos,
                                                        BoardDirectionType d) {
  /**
   *  Setup a Boundary column from Bottom (B) to Top (T)
   *  - - - - -
   *  - T - - -
   *  - x - - -
   *  - B - - -
   *  - - - - -
   */
  setupBoundary({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
  setupBoundaries(cellsPerColumn - 4, {d}, {pos[0] * cellSize[0], cellSize[1], pos[1] * cellSize[2]});
  setupBoundary({d, BoardDirectionType::TOP},
                {pos[0] * cellSize[0], (cellsPerColumn - 3) * cellSize[1], pos[1] * cellSize[2]});
}

template<>
void LinkedCellContainer<2>::setupBoundaryColumnWrapper(int cellsPerColumn, std::array<int, 2> pos,
                                                        BoardDirectionType d) {

  /**
   *  Setup a Boundary column from Bottom (B) to Top (T)
   *  - - - - -
   *  - T - - -
   *  - x - - -
   *  - B - - -
   *  - - - - -
   */
  setupBoundary({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], 0});
  setupBoundaries(cellsPerColumn - 4, {d}, {pos[0] * cellSize[0], cellSize[1]});
  setupBoundary({d, BoardDirectionType::TOP}, {pos[0] * cellSize[0], (cellsPerColumn - 3) * cellSize[1]});
}

template<>
void LinkedCellContainer<3>::setupBoundaryColumnsWrapper(int cellsPerColumn, int cellsPerRow, std::array<int, 2> pos,
                                                         BoardDirectionType d) {
  if (pos[0] == 0) {
    setupBoundary({BoardDirectionType::LEFT, d, BoardDirectionType::BOTTOM},
                  {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
    setupBoundaries(cellsPerColumn - 4, {BoardDirectionType::LEFT, d},
                    {pos[0] * cellSize[0], cellSize[1], pos[1] * cellSize[2]});
    setupBoundary({BoardDirectionType::LEFT, d, BoardDirectionType::TOP},
                  {pos[0] * cellSize[0], (cellsPerColumn - 3) * cellSize[1], pos[1] * cellSize[2]});
  } else if (pos[0] == cellsPerRow - 3) {
    setupBoundary({BoardDirectionType::RIGHT, d, BoardDirectionType::BOTTOM},
                  {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
    setupBoundaries(cellsPerColumn - 4, {BoardDirectionType::RIGHT, d},
                    {pos[0] * cellSize[0], cellSize[1], pos[1] * cellSize[2]});
    setupBoundary({BoardDirectionType::RIGHT, d, BoardDirectionType::TOP},
                  {pos[0] * cellSize[0], (cellsPerColumn - 3) * cellSize[1], pos[1] * cellSize[2]});
  } else {
    setupBoundaryColumnWrapper(cellsPerColumn, pos, d);
  }
}

template<>
void LinkedCellContainer<3>::setupCells() {
  int cellsPerRow = this->cellsPerRow() + 2;
  int cellsPerColumn = this->cellsPerColumn() + 2;
  int cellsPerDepth = this->cellsPerDepth() + 2;
  for (int z = -1; z < (cellsPerDepth - 1); ++z) {
    if (z == -1) {
      // front halo
      for (int x = -1; x < (cellsPerRow - 1); ++x) {
        setupHaloColumnsWrapper(cellsPerColumn, cellsPerRow, {x, z}, BoardDirectionType::FRONT);
      }
    } else if (z == cellsPerDepth - 2) {
      // back halo
      for (int x = -1; x < (cellsPerRow - 1); ++x) {
        setupHaloColumnsWrapper(cellsPerColumn, cellsPerRow, {x, z}, BoardDirectionType::BACK);
      }
    } else {
      for (int x = -1; x < (cellsPerRow - 1); ++x) {
        if (x == -1) {
          // left halo
          setupHaloColumnWrapper(cellsPerColumn, {x, z}, BoardDirectionType::LEFT);
        } else if (x == cellsPerRow - 2) {
          // right halo
          setupHaloColumnWrapper(cellsPerColumn, {x, z}, BoardDirectionType::RIGHT);
        } else {
          // top halo
          setupHalo({BoardDirectionType::BOTTOM}, {x * cellSize[0], -cellSize[1], z * cellSize[2]});
          if (z == 0) {
            // front boundary
            setupBoundaryColumnsWrapper(cellsPerColumn, cellsPerRow, {x, z}, BoardDirectionType::FRONT);
          } else if (z == cellsPerDepth - 3) {
            // back boundary
            setupBoundaryColumnsWrapper(cellsPerColumn, cellsPerRow, {x, z}, BoardDirectionType::BACK);
          } else if (x == 0) {
            // left boundary
            setupBoundaryColumnWrapper(cellsPerColumn, {x, z}, BoardDirectionType::LEFT);
          } else if (x == cellsPerRow - 3) {
            // right boundary
            setupBoundaryColumnWrapper(cellsPerColumn, {x, z}, BoardDirectionType::RIGHT);
          } else {
            // bottom boundary
            setupBoundary({BoardDirectionType::BOTTOM}, {x * cellSize[0], 0, z * cellSize[2]});

            // set inner
            setupInner(cellsPerColumn - 4, {x * cellSize[0], cellSize[1], z * cellSize[2]});

            // top boundary
            setupBoundary({BoardDirectionType::TOP},
                          {x * cellSize[0], (cellsPerColumn - 3) * cellSize[1], z * cellSize[2]});
          }
          // top halo
          setupHalo({BoardDirectionType::TOP}, {x * cellSize[0], (cellsPerColumn - 2) * cellSize[1], z * cellSize[2]});
        }
      }
    }
  }
}

template<>
void LinkedCellContainer<2>::setupCells() {
  int cellsPerRow = this->cellsPerRow() + 2;
  int cellsPerColumn = this->cellsPerColumn() + 2;
  for (int x = -1; x < (cellsPerRow - 1); ++x) {
    if (x == -1) {
      // left halo
      setupHaloColumnWrapper(cellsPerColumn, {x}, BoardDirectionType::LEFT);
    } else if (x == cellsPerRow - 2) {
      // right halo
      setupHaloColumnWrapper(cellsPerColumn, {x}, BoardDirectionType::RIGHT);
    } else {
      // bottom halo
      setupHalo({BoardDirectionType::BOTTOM}, {x * cellSize[0], -cellSize[1]});
      if (x == 0) {
        // left boundary
        setupBoundaryColumnWrapper(cellsPerColumn, {x}, BoardDirectionType::LEFT);
      } else if (x == cellsPerRow - 3) {
        // right boundary
        setupBoundaryColumnWrapper(cellsPerColumn, {x}, BoardDirectionType::RIGHT);
      } else {
        // bottom boundary
        setupBoundary({BoardDirectionType::BOTTOM}, {x * cellSize[0], 0});

        // set inner
        setupInner(cellsPerColumn - 4, {x * cellSize[0], cellSize[1]});

        // top boundary
        setupBoundary({BoardDirectionType::TOP}, {x * cellSize[0], (cellsPerColumn - 3) * cellSize[1]});
      }
      // top halo
      setupHalo({BoardDirectionType::TOP}, {x * cellSize[0], (cellsPerColumn - 2) * cellSize[1]});
    }
  }
}

template<>
int LinkedCellContainer<2>::getIndexBasedOnCoordinates(Vector<2> coords) {
  int cellsPerColumn = this->cellsPerColumn() + 2;
  int index = cellsPerColumn;
  index += cellsPerColumn * static_cast<int>(std::floor(coords[0] / cellSize[0]));
  index += static_cast<int>(std::floor(coords[1] / cellSize[1])) + 1;

  return index;
}

template<>
int LinkedCellContainer<3>::getIndexBasedOnCoordinates(Vector<3> coords) {
  int cellsPerRow = this->cellsPerRow() + 2;
  int cellsPerColumn = this->cellsPerColumn() + 2;

  int index = (static_cast<int>(std::floor(coords[2] / cellSize[2])) + 1) * (cellsPerRow * cellsPerColumn);
  index += cellsPerColumn;
  index += cellsPerColumn * static_cast<int>(std::floor(coords[0] / cellSize[0]));
  index += static_cast<int>(std::floor(coords[1] / cellSize[1])) + 1;

  return index;
}

template<>
void LinkedCellContainer<2>::linkHalosForPeriodic() {
  // Link Halo cells with boundary cells
  for (Halo<2> &halo: getHalosCells()) {
    auto &boardDirection = halo.getBorderDirection();
    auto &neighbours = halo.getNeighbours();
    auto &position = halo.getPosition();

    Vector<2> pos;

    if (boardDirection.size() == 1) {
      if (boardDirection[0] == BoardDirectionType::LEFT || boardDirection[0] == BoardDirectionType::RIGHT) {
        // LEFT: 1, RIGHT: 0 -> LEFT: + domain[0], RIGHT: - domain[0]
        pos = {position[0] + domain[0] * (-1 + 2 * boardDirection[0]), position[1]};
      } else if (boardDirection[0] == BoardDirectionType::TOP || boardDirection[0] == BoardDirectionType::BOTTOM) {
        // TOP: 2, BOTTOM: 3 -> TOP: - domain[1], BOTTOM: + domain[1]
        pos = {position[0], position[1] + domain[1] * (-1 + 2 * (boardDirection[0] % 2))};
      }
    } else {
      // LEFT: 1, RIGHT: 0, TOP: 2, BOTTOM: 3  -> LEFT: + domain[0], RIGHT: - domain[0], TOP: - domain[1], BOTTOM: + domain[1]
      pos = {position[0] + domain[0] * (-1 + 2 * boardDirection[0]),
             position[1] + domain[1] * (-1 + 2 * (boardDirection[1] % 2))};
    }

    // Since we calculate with double, we need to limit our precision to avoid unexpected behavior.
    pos[0] = setDoublePrecision(pos[0]);
    pos[1] = setDoublePrecision(pos[1]);
    auto index = getIndexBasedOnCoordinates(pos);
    auto *cell = cells[static_cast<unsigned long>(index)];
    neighbours.push_back(cell);
  }
}

template<>
void LinkedCellContainer<3>::linkHalosForPeriodic() {
  // Link Halo cells with boundary cells
  for (Halo<3> &halo: getHalosCells()) {
    auto &boardDirection = halo.getBorderDirection();
    auto &neighbours = halo.getNeighbours();
    auto &position = halo.getPosition();

    Vector<3> pos;

    if (boardDirection.size() == 1) {
      if (boardDirection[0] == BoardDirectionType::LEFT || boardDirection[0] == BoardDirectionType::RIGHT) {
        // LEFT: 1, RIGHT: 0 -> LEFT: + domain[0], RIGHT: - domain[0]
        pos = {position[0] + domain[0] * (-1 + 2 * boardDirection[0]), position[1], position[2]};
      } else if (boardDirection[0] == BoardDirectionType::TOP || boardDirection[0] == BoardDirectionType::BOTTOM) {
        // TOP: 2, BOTTOM: 3 -> TOP: - domain[1], BOTTOM: + domain[1]
        pos = {position[0], position[1] + domain[1] * (-1 + 2 * (boardDirection[0] % 2)), position[2]};
      } else if (boardDirection[0] == BoardDirectionType::FRONT || boardDirection[0] == BoardDirectionType::BACK) {
        // FRONT: 5, BACK: 4 -> FRONT: + domain[2], BACK: - domain[2]
        pos = {position[0], position[1], position[2] + domain[2] * (-1 + 2 * (boardDirection[0] % 2))};
      }
    } else if (boardDirection.size() == 2) {
      if ((boardDirection[0] == BoardDirectionType::LEFT || boardDirection[0] == BoardDirectionType::RIGHT)
          && (boardDirection[1] == BoardDirectionType::TOP || boardDirection[1] == BoardDirectionType::BOTTOM)) {
        // LEFT: 1, RIGHT: 0, TOP: 2, BOTTOM: 3  -> LEFT: + domain[0], RIGHT: - domain[0], TOP: - domain[1], BOTTOM: + domain[1]
        pos = {position[0] + domain[0] * (-1 + 2 * boardDirection[0]),
               position[1] + domain[1] * (-1 + 2 * (boardDirection[1] % 2)), position[2]};
      } else if ((boardDirection[0] == BoardDirectionType::LEFT || boardDirection[0] == BoardDirectionType::RIGHT)
          && (boardDirection[1] == BoardDirectionType::FRONT || boardDirection[1] == BoardDirectionType::BACK)) {
        // LEFT: 1, RIGHT: 0, FRONT: 2, BACK: 3  -> LEFT: + domain[0], RIGHT: - domain[0], FRONT: 5, BACK: 4 -> FRONT: + domain[2], BACK: - domain[2]
        pos = {position[0] + domain[0] * (-1 + 2 * boardDirection[0]), position[1],
               position[2] + domain[2] * (-1 + 2 * (boardDirection[1] % 2))};
      } else if ((boardDirection[0] == BoardDirectionType::FRONT || boardDirection[0] == BoardDirectionType::BACK)
          && (boardDirection[1] == BoardDirectionType::TOP || boardDirection[1] == BoardDirectionType::BOTTOM)) {
        // TOP: 2, BOTTOM: 3, FRONT: 2, BACK: 3  -> TOP: - domain[1], BOTTOM: + domain[1], FRONT: 5, BACK: 4 -> FRONT: + domain[2], BACK: - domain[2]
        pos = {position[0], position[1] + domain[1] * (-1 + 2 * (boardDirection[1] % 2)),
               position[2] + domain[2] * (-1 + 2 * (boardDirection[0] % 2))};
      }
    } else {
      pos = {position[0] + domain[0] * (-1 + 2 * boardDirection[0]),
             position[1] + domain[1] * (-1 + 2 * (boardDirection[2] % 2)),
             position[2] + domain[2] * (-1 + 2 * (boardDirection[1] % 2))};
    }

    // Since we calculate with double, we need to limit our precision to avoid unexpected behavior.
    pos[0] = setDoublePrecision(pos[0]);
    pos[1] = setDoublePrecision(pos[1]);
    pos[2] = setDoublePrecision(pos[2]);
    auto index = getIndexBasedOnCoordinates(pos);
    auto *cell = cells[static_cast<unsigned long>(index)];
    neighbours.push_back(cell);
  }
}

template<>
void LinkedCellContainer<2>::linkCells() {
  int cellsPerRow = this->cellsPerRow();
  int cellsPerColumn = this->cellsPerColumn();

  int maxX = static_cast<int>(std::ceil(cutoffRadius / cellSize[0]));
  int maxY = static_cast<int>(std::ceil(cutoffRadius / cellSize[1]));

  // Link Inner and Boundary Cells
  for (int x = 0; x < cellsPerRow; ++x) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      // Calculate index
      auto index = static_cast<size_t>(getIndexBasedOnCoordinates({x * cellSize[0], y * cellSize[1]}));

      // Get cell
      auto *cell = cells[index];

      // Get neighbours
      auto &neighbours = cell->getNeighbours();

      // Link periodic cells if needed
      auto &periodicCells = cell->getPeriodicNeighbours();

      // Check all possible neighbours
      for (int nX = x - maxX; nX <= x + maxX; ++nX) {
        for (int nY = y - maxY; nY <= y + maxY; ++nY) {

          // filter oneself
          if (nX == x && nY == y)
            continue;

          auto posCellX = nX * cellSize[0];
          auto posCellY = nY * cellSize[1];

          if (((nX < 0 || nX >= cellsPerRow) && this->boundaries[0] == BoundaryType::Periodic)
              || ((nY < 0 || nY >= cellsPerColumn) && this->boundaries[2] == BoundaryType::Periodic)) {

            // Calculate periodic x and periodic y position.
            auto periodicCellX = nX * cellSize[0];
            periodicCellX =
                std::fmod(periodicCellX > domain[0] ? periodicCellX - domain[0] : periodicCellX + domain[0], domain[0]);
            periodicCellX = setDoublePrecision(periodicCellX);

            auto periodicCellY = nY * cellSize[1];
            periodicCellY =
                std::fmod(periodicCellY > domain[1] ? periodicCellY - domain[1] : periodicCellY + domain[1], domain[1]);
            periodicCellY = setDoublePrecision(periodicCellY);

            if ((nX < 0 || nX >= cellsPerRow) && this->boundaries[0] != BoundaryType::Periodic) {
              continue;
            }

            if ((nY < 0 || nY >= cellsPerColumn) && this->boundaries[2] != BoundaryType::Periodic) {
              continue;
            }

            // Get periodic cell
            auto *posPeriodicCell =
                cells[static_cast<unsigned long>(getIndexBasedOnCoordinates({periodicCellX, periodicCellY}))];

            // Since we only need to build this once and want to take advantage of Newton's Law to avoid duplicates, this is not too expensive.
            std::tuple<Cell<2> *, Vector<2>> posTuple{posPeriodicCell, Vector<2>{posCellX, posCellY}};
            if (std::find_if(posPeriodicCell->getPeriodicNeighbours().begin(),
                             posPeriodicCell->getPeriodicNeighbours().end(), [&cell](auto &t) {
                  return std::get<0>(t) == cell;
                }) == posPeriodicCell->getPeriodicNeighbours().end()) {

              periodicCells.emplace_back(posTuple);
            }
          }

          if (nX < 0 || nY < 0 || nX >= cellsPerRow || nY >= cellsPerColumn)
            continue;

          // Get neighbours
          auto posNeighIndex = static_cast<size_t>(getIndexBasedOnCoordinates({posCellX, posCellY}));
          auto *posN = cells[posNeighIndex];

          // Filter already calculated cell
          if (posNeighIndex <= index) {
            continue;
          }
          // Add relevant neighbours
          neighbours.push_back(posN);
        }
      }
    }
  }

  // Link Halo cells with boundary cells
  LinkedCellContainer<2>::linkHalosForPeriodic();
}

template<>
void LinkedCellContainer<3>::linkCells() {
  int cellsPerRow = this->cellsPerRow();
  int cellsPerColumn = this->cellsPerColumn();
  int cellsPerDepth = this->cellsPerDepth();

  int maxX = static_cast<int>(std::ceil(cutoffRadius / cellSize[0]));
  int maxY = static_cast<int>(std::ceil(cutoffRadius / cellSize[1]));
  int maxZ = static_cast<int>(std::ceil(cutoffRadius / cellSize[2]));

  for (int x = 0; x < cellsPerRow; ++x) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      for (int z = 0; z < cellsPerDepth; ++z) {
        // Calculate index
        auto index =
            static_cast<size_t>(getIndexBasedOnCoordinates({x * cellSize[0], y * cellSize[1], z * cellSize[2]}));

        // Get Cell
        auto *cell = cells[index];

        // Get neighbours
        auto &neighbours = cell->getNeighbours();

        // Link periodic cells if needed
        auto &periodicCells = cell->getPeriodicNeighbours();

        for (int nX = x - maxX; nX <= x + maxX; ++nX) {
          for (int nY = y - maxY; nY <= y + maxY; ++nY) {
            for (int nZ = z - maxZ; nZ <= z + maxZ; ++nZ) {

              // filter oneself
              if (nX == x && nY == y && nZ == z)
                continue;

              auto posCellX = nX * cellSize[0];
              auto posCellY = nY * cellSize[1];
              auto posCellZ = nZ * cellSize[2];

              if (((nX < 0 || nX >= cellsPerRow) && this->boundaries[0] == BoundaryType::Periodic)
                  || ((nY < 0 || nY >= cellsPerColumn) && this->boundaries[2] == BoundaryType::Periodic)
                  || ((nZ < 0 || nZ >= cellsPerDepth) && this->boundaries[4] == BoundaryType::Periodic)) {

                // Calculate periodic x and periodic y and periodic z position.
                auto periodicCellX = nX * cellSize[0];
                periodicCellX =
                    std::fmod(periodicCellX > domain[0] ? periodicCellX - domain[0] : periodicCellX + domain[0],
                              domain[0]);
                periodicCellX = setDoublePrecision(periodicCellX);

                auto periodicCellY = nY * cellSize[1];
                periodicCellY =
                    std::fmod(periodicCellY > domain[1] ? periodicCellY - domain[1] : periodicCellY + domain[1],
                              domain[1]);
                periodicCellY = setDoublePrecision(periodicCellY);

                auto periodicCellZ = nZ * cellSize[2];
                periodicCellZ =
                    std::fmod(periodicCellZ > domain[2] ? periodicCellZ - domain[2] : periodicCellZ + domain[2],
                              domain[2]);
                periodicCellZ = setDoublePrecision(periodicCellZ);

                if ((nX < 0 || nX >= cellsPerRow) && this->boundaries[0] != BoundaryType::Periodic) {
                  continue;
                }

                if ((nY < 0 || nY >= cellsPerColumn) && this->boundaries[2] != BoundaryType::Periodic) {
                  continue;
                }

                if ((nZ < 0 || nZ >= cellsPerDepth) && this->boundaries[4] != BoundaryType::Periodic) {
                  continue;
                }

                // Get periodic cell
                auto *posPeriodicCell = cells[static_cast<size_t>(getIndexBasedOnCoordinates(
                    {periodicCellX, periodicCellY, periodicCellZ}))];

                // Since we only need to build this once and want to take advantage of Newton's Law to avoid duplicates, this is not too expensive.
                std::tuple<Cell<3> *, Vector<3>> posTuple{posPeriodicCell, Vector<3>{posCellX, posCellY, posCellZ}};
                if (std::find_if(posPeriodicCell->getPeriodicNeighbours().begin(),
                                 posPeriodicCell->getPeriodicNeighbours().end(), [&cell](auto &t) {
                      return std::get<0>(t) == cell;
                    }) == posPeriodicCell->getPeriodicNeighbours().end()) {

                  periodicCells.emplace_back(posTuple);
                }
              }

              // Filter non relevant neighbours
              if (nX < 0 || nY < 0 || nZ < 0 || nX >= cellsPerRow || nY >= cellsPerColumn || nZ >= cellsPerDepth)
                continue;

              // Get neighbour
              auto posNeighIndex = static_cast<size_t>(getIndexBasedOnCoordinates({posCellX, posCellY, posCellZ}));
              auto *posN = cells[posNeighIndex];

              // Filter already calculated cell
              if (posNeighIndex <= index) {
                continue;
              }

              // add relevant neighbours
              neighbours.push_back(posN);
            }
          }
        }
      }
    }
  }
  // Link Halo cells with boundary cells
  LinkedCellContainer<3>::linkHalosForPeriodic();
}

template<>
void LinkedCellContainer<2>::reserve() {
  int cellsPerRow = this->cellsPerRow();
  int cellsPerColumn = this->cellsPerColumn();

  auto reserveCell = (cellsPerRow + 2) * (cellsPerColumn + 2);
  auto reserveHalo = reserveCell - cellsPerRow * cellsPerColumn;
  auto reserveInner = (cellsPerRow - 2) * (cellsPerColumn - 2);
  auto reserveBoundary = (cellsPerRow * cellsPerColumn) - reserveInner;
  auto boundaryAndInner = reserveInner + reserveBoundary;

  cells.reserve(static_cast<unsigned long>(reserveCell));
  halosCells.reserve(static_cast<unsigned long>(reserveHalo));
  boundaryCells.reserve(static_cast<unsigned long>(reserveBoundary));
  innerCells.reserve(static_cast<unsigned long>(reserveInner > 0 ? reserveInner : 0));
  boundaryAndInnerCells.reserve(static_cast<unsigned long>(boundaryAndInner));

  std::cout << "Reserved " << reserveCell << " Cells!" << std::endl;
}

template<>
void LinkedCellContainer<3>::reserve() {
  int cellsPerRow = this->cellsPerRow();
  int cellsPerColumn = this->cellsPerColumn();
  int cellsPerDepth = this->cellsPerDepth();

  auto reserveCell = (cellsPerRow + 2) * (cellsPerColumn + 2) * (cellsPerDepth + 2);
  auto reserveHalo = reserveCell - cellsPerRow * cellsPerColumn * cellsPerDepth;
  auto reserveInner = (cellsPerRow - 2) * (cellsPerColumn - 2) * (cellsPerDepth - 2);
  auto reserveBoundary = (cellsPerRow * cellsPerColumn * cellsPerDepth) - reserveInner;
  auto boundaryAndInner = reserveInner + reserveBoundary;

  cells.reserve(static_cast<unsigned long>(reserveCell));
  halosCells.reserve(static_cast<unsigned long>(reserveHalo));
  boundaryCells.reserve(static_cast<unsigned long>(reserveBoundary));
  innerCells.reserve(static_cast<unsigned long>(reserveInner > 0 ? reserveInner : 0));
  boundaryAndInnerCells.reserve(static_cast<unsigned long>(boundaryAndInner));

  std::cout << "Reserved " << reserveCell << " Cells!" << std::endl;
}
