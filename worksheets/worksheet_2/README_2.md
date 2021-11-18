# MolSim - Worksheet 2

## Description

- Members: Janin Chaib, Nils Ole Harmsen and Dominik Weinzierl
- Group number: A
- Repository link: [MolSim](https://github.com/Dominik-Weinzierl/MolSim)
- Commit ID:
- Presentation as LaTex: [Slides](https://latex.tum.de/read/qskyvcxtbywk)
- Videos: [Videos](http://home.in.tum.de/~harmsen/mdpraktikum/sheet2/)

## Run application

As described in our project readme: [Readme](https://github.com/Dominik-Weinzierl/MolSim/blob/main/README.md) :)

## Changelog

- some optimization (templated simulation -> 2D/3D) -> avg. below 10 seconds
- add generators for cuboids and spheres (templated)
- add support for XML files describing the simulation (see readme for more details) -> XMLArgumentParser and XMLArgument
- add calculations with the Lennard-Jones potential (also templated)
- doxygen is no longer generated when using make all (make doc_doxygen only)
- fix remaining compiler warnings (CI test clang and gcc -> remove shadows)
- update simple parser from worksheet 1 -> now templated reusable parser
- create big test suite (50 tests) -> 3D and 2D tests for new components
- add additional benchmark flags (-b/--benchmark)
- instead of separate Vector class, instead we redefined std::array to Vector (no wrapper needed)
- add logger with 3 different sinks (Logger.h and Logger.cpp - default is deactivated for performance reasons) - be
  carefully with spdlog level trace (we trace a lot :))
