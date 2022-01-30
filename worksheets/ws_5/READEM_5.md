# MolSim - Worksheet 5

## Description

- Members: Janin Chaib, Nils Ole Harmsen and Dominik Weinzierl
- Group number: A
- Repository link: [MolSim](https://github.com/Dominik-Weinzierl/MolSim)
- Commit ID:
- Presentation as LaTex: [Slides](https://latex.tum.de/read/mnjkbqfcwmbs)
- Videos: [Videos](http://home.in.tum.de/~harmsen/mdpraktikum/sheet5/)

## Run application

As described in our project readme: [Readme](https://github.com/Dominik-Weinzierl/MolSim/blob/main/README.md) :)

## Changelog
### Task 1

- All points from the tasks are implemented and tested
- We support Molecules with multiple layers (care, this could be unstable (and is not recommended))
- We support to specify additional forces for each shape and for each particle in this shape (indexed for each shape)
- We support a custom period for each force on each particle (see Task 1 xml or xsd for reference)
- Refactoring of additional forces to support gravitation in all dimensions if required

### Task 2

- Implementation of 4 different parallelization strategies (buffer, lock-free, lock-cell, lock-optimized) -> usage defined in readme
- Check scaling with example from worksheet 4 task 2 (big in 2D)
- Different strategies (divide in independent parts, use locks, use buffer, and use a combination of locks and independent areas)
- Vtune profiles for all strategies (pros and cons in slides and in readme)

### Task 3

- Perform simulation (works fine without parallelization)

### Contest

-> Slides :)

### Task 4

- Adapt the thermostat to support the required changes (flow)
- Implement profile writer for density and velocity (see readme and slides for statistics)
- Perform simulations with different variant (readme and slides again)

### Additional

- Implement index based linking for molecules (getPositionInContainer() in Generator.cpp)
- Implement strategy to divide area in independent cells (in LinkedCellParallelLockFree constructor -> checkCorrectness(cellContainer))
- Implement tests for all new changes
- Refactoring (too many changes ^^)