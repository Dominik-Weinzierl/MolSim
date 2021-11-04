# MolSim

![CI](https://github.com/Dominik-Weinzierl/MolSim/actions/workflows/continuous_integration.yml/badge.svg)

## Description

Part of a practical course on molecular dynamics at TU Munich (IN0012). Based on a template provided
at [TUM-I5/MolSim](https://github.com/TUM-I5/MolSim).

Application for molecular simulations.

## Getting Started

Checkout the sources.

```bash
$ git clone git@github.com:Dominik-Weinzierl/MolSim.git
$ cd MolSim
```

### Prerequisites

- [cmake](https://cmake.org/)
- [gcc](https://gcc.gnu.org/)
- [clang](https://clang.llvm.org/)
- _(optional)_ [clion](https://www.jetbrains.com/clion/)
- _(optional)_ [paraview](https://www.paraview.org/)

## Run application

### Build with option `BUILD_DOCUMENTATION` disabled

<details>
  <summary>Using the Makefile</summary>

1. Create build folder and run `cmake` with `make`.

    ```bash
    $ make
    ```

   *Existing build folder will be `deleted` and `created` again.

2. Switch into your `build` folder.
   ```bash
   $ cd ./build
   ```
3. Create the `MolSim` target with the generated `Makefile`.
   ```bash
   $ make
   ```

</details>

<details>
  <summary>Using CMake</summary>

1. Create build folder (`in-source-builds` are disabled).
    ```bash
    $ mkdir ./build
    ```
2. Switch into your `build` folder.
   ```bash
   $ cd ./build
   ```
3. Run `cmake` with specified arguments.
   ```bash
   $ cmake .. -DBUILD_DOCUMENTATION=OFF -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
   ```
4. Create the `MolSim` target with the generated `Makefile`.
   ```bash
   $ make
   ```

</details>

### Build with option `BUILD_DOCUMENTATION` enabled

<details>
  <summary>Using the Makefile</summary>

1. Create build folder and run `cmake` with `make`.

    ```bash
    $ make build_with_doc
    ```

   *Existing build folder will be `deleted` and `created` again.

2. Switch into your `build` folder.
   ```bash
   $ cd ./build
   ```
3. Create the `MolSim` target with the generated `Makefile`.
   ```bash
   $ make
   ```

</details>

<details>
  <summary>Using CMake</summary>

1. Create build folder (`in-source-builds` are disabled).
    ```bash
    $ mkdir ./build
    ```
2. Switch into your `build` folder.
   ```bash
   $ cd ./build
   ```
3. Run `cmake` with specified arguments.
   ```bash
   $ cmake .. -DBUILD_DOCUMENTATION=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
   ```
4. Create the `MolSim` target with the generated `Makefile`.
   ```bash
   $ make
   ```

</details>

### Perform simulations

- Run `./MolSim` without any arguments to list possible and required arguments.
   ```bash
    $ ./MolSim
      Usage: ./MolSim
      Options:
      -h,--help               Show this help message
      -f,--filename           Specify the input filename
      -t,--t_end              Specify the end time of this simulation
      -d,--delta_t            Specify the time steps per calculation
   ```
- Run example simulation from `Worksheet 1`.
   ```bash
   $ ./MolSim --filename ../eingabe-sonne.txt --t_end 1000 --delta_t 0.014
   ```
- _(optional)_ Run example simulation from `Worksheet 1`.
   ```bash
   $ ./MolSim -f ../eingabe-sonne.txt -t 1000 -d 0.014
   ```
- _(optional)_ Run additional simulation of the solar system.
   ```bash
   $ ./MolSim -f ../sun_system.txt -t 1000 -d 0.014
   ```

### Additional Makefile commands

You need to perform the following in the top level `project` folder.
<details>
<summary>Project Makefile</summary>

- Remove the `build` folder.
   ```bash
   $ make clean
   ```
- Remove and create the `build` folder.
   ```bash
   $ make create_folder
   ```

</details>

You need to perform the following commands in the `build` folder.
<details>
  <summary>Build Makefile</summary>

- Make the `doxygen` documentation.
    ```bash
    $ make doc_doxygen
    ```
- Remove the `doxygen` documentation.
    ```bash
    $ make clean_doxygen
    ```
- Remove all target relevant files (e.g. Target, ...).
    ```bash
    $ make clean
    ```

</details>

## Contributors

Our project is developed by Dominik, Janin and Nils as part of Group A.

## License

MolSim is released under the [MIT license](https://github.com/Dominik-Weinzierl/MolSim).