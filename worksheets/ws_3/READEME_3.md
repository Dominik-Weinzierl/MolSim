# MolSim - Worksheet 3

## Description

- Members: Janin Chaib, Nils Ole Harmsen and Dominik Weinzierl
- Group number: A
- Repository link: [MolSim](https://github.com/Dominik-Weinzierl/MolSim)
- Commit ID:
- Presentation as LaTex: [Slides](https://latex.tum.de/read/mrsryyrhbsnn)
- Videos: [Videos](http://home.in.tum.de/~harmsen/mdpraktikum/sheet3/)

## Run application

As described in our project readme: [Readme](https://github.com/Dominik-Weinzierl/MolSim/blob/main/README.md) :)

## Changelog
- Extend XMLArgumentParser and XMLArgument (add additional checks)
- Improve test coverage for Parser
- Implement linked cell algorithm (4 classes: Cell, Boundary, Inner, Halo)
-> each cell knows his position and direction to the boarder (reflection and outflow is easier) 
- Add tests for cells
- Create Cell structure (setupCells) on first iteration (link cells and insert particles)
- Add simple and complex tests for linked cell simulations
- Add smooth reflection as boundary option (and outflow as well)
- Support linked cell algorithm for 2d and 3d simulations
- Add simulations and perform benchmarks
- in total 108 test cases (will be increased on the next sheet)
- Restructure folder structure and project structure
- Optimize and restructure imports as requested :)
- Add cmake options for logger
- Create simulations
- Add packed and unpacked shapes (Sphere and Cuboid)