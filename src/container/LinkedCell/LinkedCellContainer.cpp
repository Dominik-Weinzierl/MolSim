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
        setupHalos(5, cellsPerRow);
      }
    } else if (z == cellsPerDepth - 1) {
      // back halo
      for (int x = 0; x < cellsPerRow; ++x) {
        setupHalos(4, cellsPerRow);
      }
    } else {
      for (int x = 0; x < cellsPerRow; ++x) {
        if (x == 0) {
          // left halo
          setupHalos(1, cellsPerRow);
        } else if (x == cellsPerRow - 1) {
          // right halo
          setupHalos(0, cellsPerRow);
        } else {
          // top halo
          setupHalo(2);
          if (z == 1) {
            // front boundary
            setupBoundaries(5, cellsPerColumn - 2, BoardDirectionType::FRONT);
          } else if (z == cellsPerDepth - 2) {
            // back boundary
            setupBoundaries(4, cellsPerColumn - 2, BoardDirectionType::BACK);
          } else if (x == 1) {
            // left boundary
            setupBoundaries(1, cellsPerColumn - 2, BoardDirectionType::LEFT);
          } else if (x == cellsPerRow - 2) {
            // right boundary
            setupBoundaries(0, cellsPerColumn - 2, BoardDirectionType::RIGHT);
          } else {
            // top boundary
            setupBoundary(2, BoardDirectionType::TOP);

            // set inner
            setupInner(cellsPerColumn - 4);

            // bottom boundary
            setupBoundary(3, BoardDirectionType::BOTTOM);
          }
          // bottom halo
          setupHalo(3);
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
    if (x == 0) {
      // left halo
      setupHalos(1, cellsPerRow);
    } else if (x == cellsPerRow - 1) {
      // right halo
      setupHalos(0, cellsPerRow);
    } else {
      // top halo
      setupHalo(2);
      if (x == 1) {
        // left boundary
        setupBoundaries(1, cellsPerColumn - 2, BoardDirectionType::LEFT);
      } else if (x == cellsPerRow - 2) {
        // right boundary
        setupBoundaries(0, cellsPerColumn - 2, BoardDirectionType::RIGHT);
      } else {
        // top boundary
        setupBoundary(2, BoardDirectionType::TOP);

        // set inner
        setupInner(cellsPerColumn - 4);

        // bottom boundary
        setupBoundary(3, BoardDirectionType::BOTTOM);
      }
      // bottom halo
      setupHalo(3);
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

template<>
void LinkedCellContainer<2>::linkCells() {
  // TODO this needs to be adapted for cel size and cutoffRadius -> in this case we expect cutoffRadius to be cell size
  int cellsPerRow = (dimension[0] / cellSize[0]);
  int cellsPerColumn = (dimension[1] / cellSize[1]);
  for (int x = 0; x < cellsPerRow; ++x) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      auto index = static_cast<size_t>(getIndexBasedOnCoordinates(
          {static_cast<double>(x * cellSize[0]), static_cast<double>(y * cellSize[1])}));
      auto &cell = cells[index];

      auto &neighbours = cell->getNeighbours();
      auto &relevantNeighbours = cell->getRelevantNeighbours();

      for (int nX = x - 1; nX <= x + 1; ++nX) {
        for (int nY = y - 1; nY <= y + 1; ++nY) {
          // skip own
          if (nX == x && nY == y)
            continue;

          // get neighbours
          auto posNeighIndex = static_cast<size_t>(getIndexBasedOnCoordinates(
              {static_cast<double>(nX * cellSize[0]), static_cast<double>(nY * cellSize[1])}));
          auto &posN = cells[posNeighIndex];

          // add to list
          neighbours.push_back(posN.get());


          // filter non relevant neighbours
          if (nX < 0 || nY < 0 || nX >= cellsPerRow || nY >= cellsPerColumn || posNeighIndex <= index) {
            continue;
          }

          // add relevant neighbours
          relevantNeighbours.push_back(posN.get());
        }
      }
    }
  }
}

template<>
void LinkedCellContainer<3>::linkCells() {
// TODO this needs to be adapted for cel size and cutoffRadius -> in this case we expect cutoffRadius to be cell size
  int cellsPerRow = (dimension[0] / cellSize[0]);
  int cellsPerColumn = (dimension[1] / cellSize[1]);
  int cellsPerDepth = (dimension[2] / cellSize[2]);
  for (int x = 0; x < cellsPerRow; ++x) {
    for (int y = 0; y < cellsPerColumn; ++y) {
      for (int z = 0; z < cellsPerColumn; ++z) {
        auto index = static_cast<size_t>(getIndexBasedOnCoordinates(
            {static_cast<double>(x * cellSize[0]), static_cast<double>(y * cellSize[1]),
             static_cast<double>(z * cellSize[2])}));
        auto &cell = cells[index];

        auto &neighbours = cell->getNeighbours();
        auto &relevantNeighbours = cell->getRelevantNeighbours();

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
              auto &posN = cells[posNeighIndex];

              // add to list
              neighbours.push_back(posN.get());


              // filter non relevant neighbours
              if (nX < 0 || nY < 0 || nZ < 0 || nX >= cellsPerRow || nY >= cellsPerColumn || nZ >= cellsPerDepth
                  || posNeighIndex <= index) {
                continue;
              }

              // add relevant neighbours
              relevantNeighbours.push_back(posN.get());
            }
          }
        }
      }
    }
  }
}


