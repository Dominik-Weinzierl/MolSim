#include <cmath>

#include "LinkedCellContainer.h"

template<>
void LinkedCellContainer<3>::setupHaloColumnWrapper(int cellsPerColumn, std::array<int, 2> pos, BoardDirectionType d) {
  // Setup bottom halo for this specific column.
  setupHalo({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], -cellSize[1], pos[1] * cellSize[2]});
  // Setup halos in the middle of a column.
  setupHalos(cellsPerColumn - 2, {d}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
  // Setup top halos for this specific column
  setupHalo({d, BoardDirectionType::TOP},
            {pos[0] * cellSize[0], (cellsPerColumn - 2) * cellSize[1], pos[1] * cellSize[2]});
}

template<>
void LinkedCellContainer<2>::setupHaloColumnWrapper(int cellsPerColumn, std::array<int, 2> pos, BoardDirectionType d) {
  // Setup bottom halo for this specific column.
  setupHalo({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], -cellSize[1]});
  // Setup halos in the middle of a column.
  setupHalos(cellsPerColumn - 2, {d}, {pos[0] * cellSize[0], 0});
  // Setup top halos for this specific column
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

  setupBoundary({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
  setupBoundaries(cellsPerColumn - 4, {d}, {pos[0] * cellSize[0], cellSize[1], pos[1] * cellSize[2]});
  setupBoundary({d, BoardDirectionType::TOP},
                {pos[0] * cellSize[0], (cellsPerColumn - 3) * cellSize[1], pos[1] * cellSize[2]});
}

template<>
void LinkedCellContainer<2>::setupBoundaryColumnWrapper(int cellsPerColumn, std::array<int, 2> pos,
                                                        BoardDirectionType d) {

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
  int cellsPerRow = (domain[0] / cellSize[0]) + 2;
  int cellsPerColumn = (domain[1] / cellSize[1]) + 2;
  int cellsPerDepth = (domain[2] / cellSize[2]) + 2;
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
          setupHalo({BoardDirectionType::BOTTOM}, {x * cellSize[0], -cellSize[1]});
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
  int cellsPerRow = (domain[0] / cellSize[0]) + 2;
  int cellsPerColumn = (domain[1] / cellSize[1]) + 2;
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
      // bottom halo
      setupHalo({BoardDirectionType::TOP}, {x * cellSize[0], (cellsPerColumn - 2) * cellSize[1]});
    }
  }
}

template<>
int LinkedCellContainer<2>::getIndexBasedOnCoordinates(Vector<2> coords) {
  //Includes halocells
  int cellsPerColumn = (domain[1] / cellSize[1]) + 2;
  // first column is halo
  int index = cellsPerColumn;

  // Add columns until index
  index += cellsPerColumn * static_cast<int>(std::floor(coords[0] / cellSize[0]));
  // Add one halo cell
  index += static_cast<int>(std::floor(coords[1] / cellSize[1])) + 1;

  return index;
}

template<>
int LinkedCellContainer<3>::getIndexBasedOnCoordinates(Vector<3> coords) {
  int cellsPerRow = (domain[0] / cellSize[0]) + 2;
  int cellsPerColumn = (domain[1] / cellSize[1]) + 2;

  // first layers are full
  int index = (static_cast<int>(std::floor(coords[2] / cellSize[2])) + 1) * (cellsPerRow * cellsPerColumn);

  // add halo column
  index += cellsPerColumn;
  // Add columns until index
  index += cellsPerColumn * static_cast<int>(std::floor(coords[0] / cellSize[0]));
  // Add one halo cell
  index += static_cast<int>(std::floor(coords[1] / cellSize[1])) + 1;

  return index;
}

template<>
void LinkedCellContainer<2>::linkCells() {
  int cellsPerRow = (domain[0] / cellSize[0]);
  int cellsPerColumn = (domain[1] / cellSize[1]);
  // Link Inner and Boundary Cells
  for (int x = 0; x < cellsPerRow; ++x) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      // Calculate index
      auto index = static_cast<size_t>(getIndexBasedOnCoordinates(
          {static_cast<double>(x * cellSize[0]), static_cast<double>(y * cellSize[1])}));

      // Get cell
      auto *cell = cells[index];

      // Get neighbours
      auto &neighbours = cell->getNeighbours();

      // Link periodic cells if needed
      auto &periodicCells = cell->getPeriodicNeighbours();

      // Check all possible neighbours
      for (int nX = x - static_cast<int>(std::ceil(cutoffRadius / cellSize[0]));
           nX <= x + static_cast<int>(std::ceil(cutoffRadius / cellSize[0])); ++nX) {
        for (int nY = y - static_cast<int>(std::ceil(cutoffRadius / cellSize[1]));
             nY <= y + static_cast<int>(std::ceil(cutoffRadius / cellSize[1])); ++nY) {

          // filter oneself
          if (nX == x && nY == y)
            continue;

          auto posCellX = nX * cellSize[0];
          auto posCellY = nY * cellSize[1];

          if (((nX < 0 || nX >= cellsPerRow) && this->boundaries[0] == BoundaryType::Periodic)
              || ((nY < 0 || nY >= cellsPerColumn) && this->boundaries[2] == BoundaryType::Periodic)) {
            auto periodicCellX =
                ((nX * cellSize[0]) > domain[0] ? (nX * cellSize[0]) - domain[0] : (nX * cellSize[0]) + domain[0])
                    % domain[0];
            auto periodicCellY =
                ((nY * cellSize[1]) > domain[1] ? (nY * cellSize[1]) - domain[1] : (nY * cellSize[1]) + domain[1])
                    % domain[1];

            if ((nX < 0 || nX >= cellsPerRow) && (nY < 0 || nY >= cellsPerColumn)
                && (this->boundaries[0] != BoundaryType::Periodic || this->boundaries[2] != BoundaryType::Periodic)) {
              // Seems like this is only a normal halo cell, and we don't need to link it
              continue;
            }

            // left and right is periodic
            if ((nX < 0 || nX >= cellsPerRow) && (nY >= 0 && nY < cellsPerColumn)
                && this->boundaries[0] == BoundaryType::Periodic) {
              periodicCellY = nY * cellSize[1];
            } else

              // top and bottom is periodic
            if ((nY < 0 || nY >= cellsPerColumn) && (nX >= 0 && nX < cellsPerRow)
                && this->boundaries[2] == BoundaryType::Periodic) {
              periodicCellX = nX * cellSize[0];
            }

            // Get periodic cell
            auto posPeriodicCellIndex = static_cast<size_t>(getIndexBasedOnCoordinates(
                {static_cast<double>(periodicCellX), static_cast<double>(periodicCellY)}));
            auto *posPeriodicCell = cells[posPeriodicCellIndex];

            // TODO check if this is too expensive
            std::tuple<Cell<2> *, std::array<int, 2>> posTuple{posPeriodicCell, std::array<int, 2>{posCellX, posCellY}};
            if (std::find(posPeriodicCell->getPeriodicNeighbours().begin(),
                          posPeriodicCell->getPeriodicNeighbours().end(), posTuple)
                == posPeriodicCell->getPeriodicNeighbours().end()) {

              periodicCells.emplace_back(posTuple);
            }
          }

          if (nX < 0 || nY < 0 || nX >= cellsPerRow || nY >= cellsPerColumn)
            continue;

          // Get neighbours
          auto posNeighIndex = static_cast<size_t>(getIndexBasedOnCoordinates(
              {static_cast<double>(posCellX), static_cast<double>(posCellY)}));
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
  for (Halo<2> &halo: getHalosCells()) {
    auto &boardDirection = halo.getBorderDirection();
    auto &neighbours = halo.getNeighbours();
    auto &position = halo.getPosition();
    auto index = 0;
    if (boardDirection.size() == 1) {
      if (boardDirection[0] == BoardDirectionType::LEFT) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1])});
      } else if (boardDirection[0] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0]), static_cast<double>(position[1] - domain[1])});
      } else if (boardDirection[0] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0]), static_cast<double>(position[1] + domain[1])});
      }
    } else {
      if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1] - domain[1])});
      } else if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1] + domain[1])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1] - domain[1])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1] + domain[1])});
      }
    }
    auto *cell = cells[static_cast<unsigned long>(index)];
    neighbours.push_back(cell);
  }
}

template<>
void LinkedCellContainer<3>::linkCells() {
  int cellsPerRow = (domain[0] / cellSize[0]);
  int cellsPerColumn = (domain[1] / cellSize[1]);
  int cellsPerDepth = (domain[2] / cellSize[2]);

  for (int x = 0; x < cellsPerRow; ++x) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      for (int z = 0; z < cellsPerDepth; ++z) {
        // Calculate index
        auto index = static_cast<size_t>(getIndexBasedOnCoordinates(
            {static_cast<double>(x * cellSize[0]), static_cast<double>(y * cellSize[1]),
             static_cast<double>(z * cellSize[2])}));

        // Get Cell
        auto *cell = cells[index];

        // Get neighbours
        auto &neighbours = cell->getNeighbours();

        // Link periodic cells if needed
        auto &periodicCells = cell->getPeriodicNeighbours();

        for (int nX = x - static_cast<int>(std::ceil(cutoffRadius / cellSize[0]));
             nX <= x + static_cast<int>(std::ceil(cutoffRadius / cellSize[0])); ++nX) {
          for (int nY = y - static_cast<int>(std::ceil(cutoffRadius / cellSize[1]));
               nY <= y + static_cast<int>(std::ceil(cutoffRadius / cellSize[1])); ++nY) {
            for (int nZ = z - static_cast<int>(std::ceil(cutoffRadius / cellSize[2]));
                 nZ <= z + static_cast<int>(std::ceil(cutoffRadius / cellSize[2])); ++nZ) {

              // filter oneself
              if (nX == x && nY == y && nZ == z)
                continue;

              auto posCellX = nX * cellSize[0];
              auto posCellY = nY * cellSize[1];
              auto posCellZ = nZ * cellSize[2];

              if (((nX < 0 || nX >= cellsPerRow) && this->boundaries[0] == BoundaryType::Periodic)
                  || ((nY < 0 || nY >= cellsPerColumn) && this->boundaries[2] == BoundaryType::Periodic)
                  || ((nZ < 0 || nZ >= cellsPerDepth) && this->boundaries[4] == BoundaryType::Periodic)) {
                auto periodicCellX =
                    ((nX * cellSize[0]) > domain[0] ? (nX * cellSize[0]) - domain[0] : (nX * cellSize[0]) + domain[0])
                        % domain[0];
                auto periodicCellY =
                    ((nY * cellSize[1]) > domain[1] ? (nY * cellSize[1]) - domain[1] : (nY * cellSize[1]) + domain[1])
                        % domain[1];
                auto periodicCellZ =
                    ((nZ * cellSize[2]) > domain[2] ? (nZ * cellSize[2]) - domain[2] : (nZ * cellSize[2]) + domain[2])
                        % domain[2];

                // left/right and top/bottom and back/front
                if ((nX < 0 || nX >= cellsPerRow) && (nY < 0 || nY >= cellsPerColumn) && (nZ < 0 || nZ >= cellsPerDepth)
                    && (this->boundaries[0] != BoundaryType::Periodic || this->boundaries[2] != BoundaryType::Periodic
                        || this->boundaries[4] != BoundaryType::Periodic)) {
                  // Seems like this is only a normal halo cell, and we don't need to link it
                  continue;
                }

                // left and right is periodic
                if ((nX < 0 || nX >= cellsPerRow) && (nY >= 0 && nY < cellsPerColumn) && (nZ >= 0 && nZ < cellsPerDepth)
                    && this->boundaries[0] == BoundaryType::Periodic) {
                  periodicCellY = nY * cellSize[1];
                  periodicCellZ = nZ * cellSize[2];
                } else

                  // top and bottom is periodic
                if ((nY < 0 || nY >= cellsPerColumn) && (nX >= 0 && nX < cellsPerRow) && (nZ >= 0 && nZ < cellsPerDepth)
                    && this->boundaries[2] == BoundaryType::Periodic) {
                  periodicCellX = nX * cellSize[0];
                  periodicCellZ = nZ * cellSize[2];
                } else

                  // front and back is periodic
                if ((nZ < 0 || nZ >= cellsPerDepth) && (nY >= 0 || nY < cellsPerColumn) && (nX >= 0 && nX < cellsPerRow)
                    && this->boundaries[4] == BoundaryType::Periodic) {
                  periodicCellX = nX * cellSize[0];
                  periodicCellY = nY * cellSize[1];
                } else

                  // top/bottom and left/right
                if ((nY < 0 || nY >= cellsPerColumn) && (nX < 0 || nX >= cellsPerRow) && (nZ >= 0 && nZ < cellsPerDepth)
                    && this->boundaries[2] == BoundaryType::Periodic && this->boundaries[0] == BoundaryType::Periodic) {
                  periodicCellZ = nZ * cellSize[2];
                } else

                  // top/bottom and front/back
                if ((nY < 0 || nY >= cellsPerColumn) && (nZ < 0 || nZ >= cellsPerDepth) && (nX >= 0 && nX < cellsPerRow)
                    && this->boundaries[2] == BoundaryType::Periodic && this->boundaries[4] == BoundaryType::Periodic) {
                  periodicCellX = nX * cellSize[0];
                } else

                  // left/right and front/back
                if ((nX < 0 || nX >= cellsPerRow) && (nZ < 0 || nZ >= cellsPerDepth) && (nY >= 0 && nY < cellsPerColumn)
                    && this->boundaries[0] == BoundaryType::Periodic && this->boundaries[4] == BoundaryType::Periodic) {
                  periodicCellY = nY * cellSize[1];
                }

                // Get periodic cell
                auto posPeriodicCellIndex = static_cast<size_t>(getIndexBasedOnCoordinates(
                    {static_cast<double>(periodicCellX), static_cast<double>(periodicCellY),
                     static_cast<double>(periodicCellZ)}));
                auto *posPeriodicCell = cells[posPeriodicCellIndex];

                // TODO check if this is too expensive
                std::tuple<Cell<3> *, std::array<int, 3>> posTuple{posPeriodicCell, std::array<int, 3>{posCellX, posCellY, posCellZ}};
                if (std::find(posPeriodicCell->getPeriodicNeighbours().begin(),
                              posPeriodicCell->getPeriodicNeighbours().end(), posTuple)
                    == posPeriodicCell->getPeriodicNeighbours().end()) {

                  periodicCells.emplace_back(posTuple);
                }
              }

              // Filter non relevant neighbours
              if (nX < 0 || nY < 0 || nZ < 0 || nX >= cellsPerRow || nY >= cellsPerColumn || nZ >= cellsPerDepth)
                continue;

              // Get neighbour
              auto posNeighIndex = static_cast<size_t>(getIndexBasedOnCoordinates(
                  {static_cast<double>(posCellX), static_cast<double>(posCellY),
                   static_cast<double>(posCellZ)}));
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
  for (Halo<3> &halo: getHalosCells()) {
    auto &boardDirection = halo.getBorderDirection();
    auto &neighbours = halo.getNeighbours();
    auto &position = halo.getPosition();
    auto index = 0;
    if (boardDirection.size() == 1) {
      if (boardDirection[0] == BoardDirectionType::LEFT) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1]),
             static_cast<double>(position[2])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1]),
             static_cast<double>(position[2])});
      } else if (boardDirection[0] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0]), static_cast<double>(position[1] - domain[1]),
             static_cast<double>(position[2])});
      } else if (boardDirection[0] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0]), static_cast<double>(position[1] + domain[1]),
             static_cast<double>(position[2])});
      } else if (boardDirection[0] == BoardDirectionType::FRONT) {
        index = getIndexBasedOnCoordinates({static_cast<double>(position[0]), static_cast<double>(position[1]),
                                            static_cast<double>(position[2] + domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::BACK) {
        index = getIndexBasedOnCoordinates({static_cast<double>(position[0]), static_cast<double>(position[1]),
                                            static_cast<double>(position[2] - domain[2])});
      }
    } else if (boardDirection.size() == 2) {
      if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1] - domain[1]),
             static_cast<double>(position[2])});
      } else if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1] + domain[1]),
             static_cast<double>(position[2])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1] - domain[1]),
             static_cast<double>(position[2])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1] + domain[1]),
             static_cast<double>(position[2])});
      } else if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::FRONT) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1]),
             static_cast<double>(position[2] + domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::FRONT) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1]),
             static_cast<double>(position[2] + domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::BACK) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1]),
             static_cast<double>(position[2] - domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::BACK) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1]),
             static_cast<double>(position[2] - domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::FRONT && boardDirection[1] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0]), static_cast<double>(position[1] - domain[1]),
             static_cast<double>(position[2] + domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::FRONT && boardDirection[1] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0]), static_cast<double>(position[1] + domain[1]),
             static_cast<double>(position[2] + domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::BACK && boardDirection[1] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0]), static_cast<double>(position[1] - domain[1]),
             static_cast<double>(position[2] - domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::BACK && boardDirection[1] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0]), static_cast<double>(position[1] + domain[1]),
             static_cast<double>(position[2] - domain[2])});
      }
    } else {
      // front
      if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::FRONT
          && boardDirection[2] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1] + domain[1]),
             static_cast<double>(position[2] + domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::FRONT
          && boardDirection[2] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1] + domain[1]),
             static_cast<double>(position[2] + domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::FRONT
          && boardDirection[2] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1] - domain[1]),
             static_cast<double>(position[2] + domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::FRONT
          && boardDirection[2] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1] - domain[1]),
             static_cast<double>(position[2] + domain[2])});
      } else
        // back
      if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::BACK
          && boardDirection[2] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1] + domain[1]),
             static_cast<double>(position[2] - domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::BACK
          && boardDirection[2] == BoardDirectionType::BOTTOM) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1] + domain[1]),
             static_cast<double>(position[2] - domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::LEFT && boardDirection[1] == BoardDirectionType::BACK
          && boardDirection[2] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] + domain[0]), static_cast<double>(position[1] - domain[1]),
             static_cast<double>(position[2] - domain[2])});
      } else if (boardDirection[0] == BoardDirectionType::RIGHT && boardDirection[1] == BoardDirectionType::BACK
          && boardDirection[2] == BoardDirectionType::TOP) {
        index = getIndexBasedOnCoordinates(
            {static_cast<double>(position[0] - domain[0]), static_cast<double>(position[1] - domain[1]),
             static_cast<double>(position[2] - domain[2])});
      }
    }
    auto *cell = cells[static_cast<unsigned long>(index)];
    neighbours.push_back(cell);
  }
}

template<>
void LinkedCellContainer<2>::reserve() {
  int cellsPerRow = (domain[0] / cellSize[0]);
  int cellsPerColumn = (domain[1] / cellSize[1]);

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
  int cellsPerRow = (domain[0] / cellSize[0]);
  int cellsPerColumn = (domain[1] / cellSize[1]);
  int cellsPerDepth = (domain[2] / cellSize[2]);

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
