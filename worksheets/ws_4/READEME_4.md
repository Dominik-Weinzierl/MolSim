# MolSim - Worksheet 4

## Description

- Members: Janin Chaib, Nils Ole Harmsen and Dominik Weinzierl
- Group number: A
- Repository link: [MolSim](https://github.com/Dominik-Weinzierl/MolSim)
- Commit ID:
- Presentation as LaTex: [Slides]()
- Videos: [Videos](http://home.in.tum.de/~harmsen/mdpraktikum/sheet4/)

## Run application

As described in our project readme: [Readme](https://github.com/Dominik-Weinzierl/MolSim/blob/main/README.md) :)

## Changelog
- Add support for thermostats
- Add support for additional gravitation
- Add support for mixed lennard jones parameters 
- Add support for checkpointing (reuse of vtk logic)
- Add tests for all new features
- Support double as cell size and domain size (some limitations ->  the cell size must be a divisor of the domain size)
- Perform benchmarks on cluster (and local machines)
- Rethink some logic and evaluate performance (seems we are always storage bound, not cpu bound)