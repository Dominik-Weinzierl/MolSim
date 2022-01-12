#include "LinkedCellParallelLockFree.h"

template<>
LinkedCellParallelLockFree<LennardJones, 3>::LinkedCellParallelLockFree(double cutoffRadius, Vector<3> cellSize,
                                                                        ParticleContainer<3> &particleContainer) {
  auto maxX = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[0])) + 2;
  auto maxY = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[1])) + 2;
  auto maxZ = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[2])) + 1;

  auto &cellContainer = dynamic_cast<LinkedCellContainer<3> &>(particleContainer);

  auto cellsPerLayer = static_cast<unsigned long>(cellContainer.cellsPerColumn())
      * static_cast<unsigned long>(cellContainer.cellsPerRow());
  auto cellsPerColumn = static_cast<unsigned long>(cellContainer.cellsPerColumn());

  for (size_t z = 0; z < maxZ; ++z) {
    for (size_t x = 0; x < maxX; ++x) {
      for (size_t y = 0; y < maxY; ++y) {
        std::vector<Cell<3> *> cellVector;
        size_t row = x;
        size_t depth = z;
        size_t counter = row * cellsPerColumn + depth * cellsPerLayer + y;

        while (counter < cellContainer.getBoundaryAndInnerCells().size()) {
          cellVector.push_back(cellContainer.getBoundaryAndInnerCells()[counter]);

          if (counter + maxY >= ((row + 1) * cellsPerColumn) + depth * cellsPerLayer) {
            row += maxX;
            counter = row * cellsPerColumn + depth * cellsPerLayer + y;

            if (counter >= ((depth + 1) * cellsPerLayer)) {
              depth += maxZ;
              row = x;
              counter = row * cellsPerColumn + depth * cellsPerLayer + y;
            }

          } else {
            counter += maxY;
          }
        }
        cells.push_back(cellVector);
      }
    }
  }

  checkCorrectness(cellContainer);
}

template<>
LinkedCellParallelLockFree<LennardJones, 2>::LinkedCellParallelLockFree(double cutoffRadius, Vector<2> cellSize,
                                                                        ParticleContainer<2> &particleContainer) {
  auto maxX = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[0])) + 1;
  auto maxY = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[1])) + 2;

  auto &cellContainer = dynamic_cast<LinkedCellContainer<2> &>(particleContainer);

  auto cellsPerColumn = static_cast<unsigned long>(cellContainer.cellsPerColumn());

  for (size_t x = 0; x < maxX; ++x) {
    for (size_t y = 0; y < maxY; ++y) {
      std::vector<Cell<2> *> cellVector;
      size_t row = x;
      size_t counter = row * cellsPerColumn + y;
      while (counter < cellContainer.getBoundaryAndInnerCells().size()) {
        cellVector.push_back(cellContainer.getBoundaryAndInnerCells()[counter]);

        if (counter + maxY >= ((row + 1) * cellsPerColumn)) {
          row += maxX;
          counter = row * cellsPerColumn + y;
        } else {
          counter += maxY;
        }
      }
      cells.push_back(cellVector);
    }
  }

  checkCorrectness(cellContainer);
}