#include "LinkedCellContainer.h"

template<>
void LinkedCellContainer<3>::setupHaloColumnWrapper(int cellsPerColumn, std::array<int, 2> pos, BoardDirectionType d) {
  setupHalo({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], -cellSize[1], pos[1] * cellSize[2]});
  setupHalos(cellsPerColumn - 2, {d}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
  setupHalo({d, BoardDirectionType::TOP},
            {pos[0] * cellSize[0], (cellsPerColumn - 2) * cellSize[1], pos[1] * cellSize[2]});
}

template<>
void LinkedCellContainer<2>::setupHaloColumnWrapper(int cellsPerColumn, std::array<int, 2> pos, BoardDirectionType d) {
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

  setupBoundary({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
  setupBoundaries(cellsPerColumn - 4, {d}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
  setupBoundary({d, BoardDirectionType::TOP},
                {pos[0] * cellSize[0], (cellsPerColumn - 3) * cellSize[1], pos[1] * cellSize[2]});
}

template<>
void LinkedCellContainer<2>::setupBoundaryColumnWrapper(int cellsPerColumn, std::array<int, 2> pos,
                                                        BoardDirectionType d) {

  setupBoundary({d, BoardDirectionType::BOTTOM}, {pos[0] * cellSize[0], 0});
  setupBoundaries(cellsPerColumn - 4, {d}, {pos[0] * cellSize[0], 0});
  setupBoundary({d, BoardDirectionType::TOP}, {pos[0] * cellSize[0], (cellsPerColumn - 3) * cellSize[1]});
}

template<>
void LinkedCellContainer<3>::setupBoundaryColumnsWrapper(int cellsPerColumn, int cellsPerRow, std::array<int, 2> pos,
                                                         BoardDirectionType d) {
  if (pos[0] == 0) {
    setupBoundary({BoardDirectionType::LEFT, d, BoardDirectionType::BOTTOM},
                  {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
    setupBoundaries(cellsPerColumn - 4, {BoardDirectionType::LEFT, d}, {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
    setupBoundary({BoardDirectionType::LEFT, d, BoardDirectionType::TOP},
                  {pos[0] * cellSize[0], (cellsPerColumn - 3) * cellSize[1], pos[1] * cellSize[2]});
  } else if (pos[0] == cellsPerRow - 3) {
    setupBoundary({BoardDirectionType::RIGHT, d, BoardDirectionType::BOTTOM},
                  {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
    setupBoundaries(cellsPerColumn - 4, {BoardDirectionType::RIGHT, d},
                    {pos[0] * cellSize[0], 0, pos[1] * cellSize[2]});
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
  index += cellsPerColumn * static_cast<int>((coords[0] / cellSize[0]));
  // Add one halo cell
  index += static_cast<int>((coords[1] / cellSize[1])) + 1;

  return index;
}

template<>
int LinkedCellContainer<3>::getIndexBasedOnCoordinates(Vector<3> coords) {
  int cellsPerRow = (domain[0] / cellSize[0]) + 2;
  int cellsPerColumn = (domain[1] / cellSize[1]) + 2;

  // first layers are full
  int index = (static_cast<int>((coords[2] / cellSize[2])) + 1) * (cellsPerRow * cellsPerColumn);

  // add halo column
  index += cellsPerColumn;
  // Add columns until index
  index += cellsPerColumn * static_cast<int>((coords[0] / cellSize[0]));
  // Add one halo cell
  index += static_cast<int>((coords[1] / cellSize[1])) + 1;

  return index;
}

template<>
void LinkedCellContainer<2>::linkCells() {
  int cellsPerRow = (domain[0] / cellSize[0]);
  int cellsPerColumn = (domain[1] / cellSize[1]);
  for (int x = 0; x < cellsPerRow; ++x) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      // Calculate index
      auto index = static_cast<size_t>(getIndexBasedOnCoordinates(
          {static_cast<double>(x * cellSize[0]), static_cast<double>(y * cellSize[1])}));

      // Get cell
      auto *cell = cells[index];

      // Get neighbours
      auto &neighbours = cell->getNeighbours();

      // Check all possible neighbours
      for (int nX = x - static_cast<int>(cutoffRadius / cellSize[0]);
           nX <= x + static_cast<int>(cutoffRadius / cellSize[0]); ++nX) {
        for (int nY = y - static_cast<int>(cutoffRadius / cellSize[1]);
             nY <= y + static_cast<int>(cutoffRadius / cellSize[1]); ++nY) {

          // Filter non relevant neighbours
          if ((nX == x && nY == y) || nX < 0 || nY < 0 || nX >= cellsPerRow || nY >= cellsPerColumn)
            continue;

          // Get neighbours
          auto posNeighIndex = static_cast<size_t>(getIndexBasedOnCoordinates(
              {static_cast<double>(nX * cellSize[0]), static_cast<double>(nY * cellSize[1])}));
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
}

// TODO CLEAN UP!!

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

        for (int nX = x - static_cast<int>(cutoffRadius / cellSize[0]);
             nX <= x + static_cast<int>(cutoffRadius / cellSize[0]); ++nX) {
          for (int nY = y - static_cast<int>(cutoffRadius / cellSize[1]);
               nY <= y + static_cast<int>(cutoffRadius / cellSize[1]); ++nY) {
            for (int nZ = z - static_cast<int>(cutoffRadius / cellSize[2]);
                 nZ <= z + static_cast<int>(cutoffRadius / cellSize[2]); ++nZ) {

              // Filter non relevant neighbours
              if ((nX == x && nY == y && nZ == z) || nX < 0 || nY < 0 || nZ < 0 || nX >= cellsPerRow
                  || nY >= cellsPerColumn || nZ >= cellsPerDepth)
                continue;

              // Get neighbour
              auto posNeighIndex = static_cast<size_t>(getIndexBasedOnCoordinates(
                  {static_cast<double>(nX * cellSize[0]), static_cast<double>(nY * cellSize[1]),
                   static_cast<double>(nZ * cellSize[2])}));
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


