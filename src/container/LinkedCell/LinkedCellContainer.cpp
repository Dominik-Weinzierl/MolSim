#include "LinkedCellContainer.h"

template<>
void LinkedCellContainer<3>::setupCells() {
  int cellsPerRow = (dimension[0] / cellSize[0]) + 2;
  int cellsPerColumn = (dimension[1] / cellSize[1]) + 2;
  int cellsPerDepth = (dimension[2] / cellSize[2]) + 2;
  for (int z = 0; z < cellsPerDepth; ++z) {
    if (z == 0) {
      // front halo
      for (int x = 0; x < cellsPerRow; ++x) {
        setupHalos(5, cellsPerRow, std::array<int, 3>{x * cellSize[0], 0, z * cellSize[2]});
      }
    } else if (z == cellsPerDepth - 1) {
      // back halo
      for (int x = 0; x < cellsPerRow; ++x) {
        setupHalos(4, cellsPerRow, std::array<int, 3>{x * cellSize[0], 0, z * cellSize[2]});
      }
    } else {
      for (int x = 0; x < cellsPerRow; ++x) {
        std::array<int, 3> pos{x * cellSize[0], 0, z * cellSize[2]};
        if (x == 0) {
          // left halo
          setupHalos(1, cellsPerRow, pos);
        } else if (x == cellsPerRow - 1) {
          // right halo
          setupHalos(0, cellsPerRow, pos);
        } else {
          // top halo
          setupHalo(2, pos);
          if (z == 1) {
            // front boundary
            setupBoundaries(5, cellsPerColumn - 2, BoardDirectionType::FRONT, pos);
          } else if (z == cellsPerDepth - 2) {
            // back boundary
            setupBoundaries(4, cellsPerColumn - 2, BoardDirectionType::BACK, pos);
          } else if (x == 1) {
            // left boundary
            setupBoundaries(1, cellsPerColumn - 2, BoardDirectionType::LEFT, pos);
          } else if (x == cellsPerRow - 2) {
            // right boundary
            setupBoundaries(0, cellsPerColumn - 2, BoardDirectionType::RIGHT, pos);
          } else {
            // top boundary
            setupBoundary(2, BoardDirectionType::TOP, pos);

            // set inner
            setupInner(cellsPerColumn - 4, pos);

            // bottom boundary
            pos[1] = cellsPerColumn - 2;
            setupBoundary(3, BoardDirectionType::BOTTOM, pos);
          }
          // bottom halo
          pos[1] = cellsPerColumn - 1;
          setupHalo(3, pos);
        }
      }
    }
  }
}

template<>
void LinkedCellContainer<2>::setupCells() {
  int cellsPerRow = (dimension[0] / cellSize[0]) + 2;
  int cellsPerColumn = (dimension[1] / cellSize[1]) + 2;
  for (int x = 0; x < cellsPerRow; ++x) {
    std::array<int, 2> pos{x * cellSize[0], 0};
    if (x == 0) {
      // left halo
      setupHalos(1, cellsPerRow, pos);
    } else if (x == cellsPerRow - 1) {
      // right halo
      setupHalos(0, cellsPerRow, pos);
    } else {
      // top halo
      setupHalo(2, pos);
      if (x == 1) {
        // left boundary
        setupBoundaries(1, cellsPerColumn - 2, BoardDirectionType::LEFT, pos);
      } else if (x == cellsPerRow - 2) {
        // right boundary
        setupBoundaries(0, cellsPerColumn - 2, BoardDirectionType::RIGHT, pos);
      } else {
        // top boundary
        setupBoundary(2, BoardDirectionType::TOP, pos);

        // set inner
        setupInner(cellsPerColumn - 4, pos);

        // bottom boundary
        pos[1] = cellsPerColumn - 2;
        setupBoundary(3, BoardDirectionType::BOTTOM, pos);
      }
      // bottom halo
      pos[1] = cellsPerColumn - 1;
      setupHalo(3, pos);
    }
  }
}

template<>
int LinkedCellContainer<2>::getIndexBasedOnCoordinates(Vector<2> coords) {
  int cellsPerColumn = (dimension[1] / cellSize[1]) + 2;
  // first column is halo
  int index = cellsPerColumn;

  // Add columns until index
  index += cellsPerColumn * static_cast<int>((coords[0] / cellSize[0]));
  // Add one halo cell
  index += static_cast<int>((coords[1] / cellSize[1])) + 1;

  return index;
}

template<>
int LinkedCellContainer<3>::getIndexBasedOnCoordinates(Vector<3> coords) {
  int cellsPerRow = (dimension[0] / cellSize[0]) + 2;
  int cellsPerColumn = (dimension[1] / cellSize[1]) + 2;
  int cellsPerLayer = cellsPerRow * cellsPerColumn;

  // first layers are full
  int index = cellsPerLayer + static_cast<int>((coords[2] / cellSize[1])) * cellsPerLayer;

  // add halo column
  index += cellsPerColumn;
  // Add columns until index
  index += cellsPerColumn * static_cast<int>((coords[0] / cellSize[0]));
  // Add one halo cell
  index += static_cast<int>((coords[1] / cellSize[1])) + 1;

  return index;
}

// TODO CLEAN UP!!

template<>
void LinkedCellContainer<2>::linkCells() {
  // TODO this needs to be adapted for cel size and cutoffRadius -> in this case we expect cutoffRadius to be cell size
  int cellsPerRow = (dimension[0] / cellSize[0]);
  int cellsPerColumn = (dimension[1] / cellSize[1]);
  for (int x = 0; x < cellsPerRow; ++x) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      auto index = static_cast<size_t>(getIndexBasedOnCoordinates(
          {static_cast<double>(x * cellSize[0]), static_cast<double>(y * cellSize[1])}));
      auto *cell = cells[index];

      auto &neighbours = cell->getNeighbours();

      for (int nX = x - 1; nX <= x + 1; ++nX) {
        for (int nY = y - 1; nY <= y + 1; ++nY) {
          // skip own
          if (nX == x && nY == y)
            continue;

          // get neighbours
          auto posNeighIndex = static_cast<size_t>(getIndexBasedOnCoordinates(
              {static_cast<double>(nX * cellSize[0]), static_cast<double>(nY * cellSize[1])}));
          auto *posN = cells[posNeighIndex];

          // filter non relevant neighbours
          if (nX < 0 || nY < 0 || nX >= cellsPerRow || nY >= cellsPerColumn || posNeighIndex <= index) {
            continue;
          }

          // add relevant neighbours
          neighbours.push_back(posN);
        }
      }
    }
  }
}

// TODO CLEAN UP!!

template<>
void LinkedCellContainer<3>::linkCells() {
// TODO this needs to be adapted for cel size and cutoffRadius -> in this case we expect cutoffRadius to be cell size
  int cellsPerRow = (dimension[0] / cellSize[0]);
  int cellsPerColumn = (dimension[1] / cellSize[1]);
  int cellsPerDepth = (dimension[2] / cellSize[2]);
  for (int x = 0; x < cellsPerRow; ++x) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      for (int z = 0; z < cellsPerDepth; ++z) {
        auto index = static_cast<size_t>(getIndexBasedOnCoordinates(
            {static_cast<double>(x * cellSize[0]), static_cast<double>(y * cellSize[1]),
             static_cast<double>(z * cellSize[2])}));
        auto *cell = cells[index];

        auto &neighbours = cell->getNeighbours();

        for (int nX = x - 1; nX <= x + 1; ++nX) {
          for (int nY = y - 1; nY <= y + 1; ++nY) {
            for (int nZ = z - 1; nZ <= z + 1; ++nZ) {
              // skip own
              if (nX == x && nY == y && nZ == z)
                continue;

              // get neighbours
              auto posNeighIndex = static_cast<size_t>(getIndexBasedOnCoordinates(
                  {static_cast<double>(nX * cellSize[0]), static_cast<double>(nY * cellSize[1]),
                   static_cast<double>(nZ * cellSize[2])}));
              auto *posN = cells[posNeighIndex];

              // filter non relevant neighbours
              if (nX < 0 || nY < 0 || nZ < 0 || nX >= cellsPerRow || nY >= cellsPerColumn || nZ >= cellsPerDepth
                  || posNeighIndex <= index) {
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
}

template<>
void LinkedCellContainer<2>::reserve() {
  int cellsPerRow = (dimension[0] / cellSize[0]);
  int cellsPerColumn = (dimension[1] / cellSize[1]);

  auto reserveCell = (cellsPerRow + 2) * (cellsPerColumn + 2);
  auto reserveHalo = reserveCell - cellsPerRow * cellsPerColumn;
  auto reserveInner = (cellsPerRow - 2) * (cellsPerColumn - 2);
  auto reserveBoundary = (cellsPerRow * cellsPerColumn) - reserveInner;
  auto boundaryAndInner = reserveInner + reserveBoundary;

  cells.reserve(static_cast<unsigned long>(reserveCell));
  halosCells.reserve(static_cast<unsigned long>(reserveHalo));
  boundaryCells.reserve(static_cast<unsigned long>(reserveBoundary));
  innerCells.reserve(static_cast<unsigned long>(reserveInner));
  boundaryAndInnerCells.reserve(static_cast<unsigned long>(boundaryAndInner));
}

template<>
void LinkedCellContainer<3>::reserve() {
  int cellsPerRow = (dimension[0] / cellSize[0]);
  int cellsPerColumn = (dimension[1] / cellSize[1]);
  int cellsPerDepth = (dimension[2] / cellSize[2]);

  auto reserveCell = (cellsPerRow + 2) * (cellsPerColumn + 2) * (cellsPerDepth + 2);
  auto reserveHalo = reserveCell - cellsPerRow * cellsPerColumn * cellsPerDepth;
  auto reserveInner = (cellsPerRow - 2) * (cellsPerColumn - 2) * (cellsPerDepth - 2);
  auto reserveBoundary = (cellsPerRow * cellsPerColumn * cellsPerDepth) - reserveInner;
  auto boundaryAndInner = reserveInner + reserveBoundary;

  cells.reserve(static_cast<unsigned long>(reserveCell));
  halosCells.reserve(static_cast<unsigned long>(reserveHalo));
  boundaryCells.reserve(static_cast<unsigned long>(reserveBoundary));
  innerCells.reserve(static_cast<unsigned long>(reserveInner));
  boundaryAndInnerCells.reserve(static_cast<unsigned long>(boundaryAndInner));
}


