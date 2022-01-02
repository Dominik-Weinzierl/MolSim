#include "LinkedCellParallelLockFree.h"

template<>
LinkedCellParallelLockFree<LennardJones, 3>::LinkedCellParallelLockFree(double cutoffRadius, Vector<3> cellSize,
                                                                        ParticleContainer<3> &particleContainer) {
  auto maxX = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[0]));
  auto maxY = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[1])) + 1;
  auto maxZ = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[2]));

  (void) maxX;
  (void) maxY;
  (void) maxZ;
  (void) particleContainer;
}

template<>
LinkedCellParallelLockFree<LennardJones, 2>::LinkedCellParallelLockFree(double cutoffRadius, Vector<2> cellSize,
                                                                        ParticleContainer<2> &particleContainer) {
  auto maxX = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[0])) + 1;
  auto maxY = static_cast<size_t>(std::ceil(cutoffRadius / cellSize[1])) + 2;

  // TODO add check
  auto &cellContainer = dynamic_cast<LinkedCellContainer<2> &>(particleContainer);

  for (size_t x = 0; x < maxX; ++x) {
    for (size_t y = 0; y < maxY; ++y) {
      std::vector<Cell<2> *> cellVector;
      size_t row = x;
      size_t counter = row * static_cast<unsigned long>(cellContainer.cellsPerColumn()) + y;
      while (counter < cellContainer.getBoundaryAndInnerCells().size()) {
        cellVector.push_back(cellContainer.getBoundaryAndInnerCells()[counter]);

        if (counter + maxY >= ((row + 1) * static_cast<unsigned long>(cellContainer.cellsPerColumn()))) {
          row += maxX;
          counter = row * static_cast<unsigned long>(cellContainer.cellsPerColumn()) + y;
        } else {
          counter += maxY;
        }
      }
      cells.push_back(cellVector);
    }
  }
}