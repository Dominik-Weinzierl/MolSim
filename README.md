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

### Build

#### Available build options:

- BUILD_DOCUMENTATION: Enables build of doxygen documentation (default: off)
- BUILD_TESTS: Enable build of tests (default: off)

#### Using the Makefile:

1. Create build folder and run cmake with make.
    ```bash
    $ make
    ```
   *Existing build folder will be deleted and created again.

2. Switch into your build folder.
   ```bash
   $ cd ./build
   ```
3. Create the MolSim target with the generated Makefile.
   ```bash
   $ make
   ```

#### Using CMake:

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
   $ cmake .. -D BUILD_DOCUMENTATION=OFF -D BUILD_TESTS=OFF -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++
   ```
4. Create the MolSim target with the generated Makefile.
   ```bash
   $ make
   ```

### Perform simulations

- Run `./MolSim` without any arguments to list possible and required arguments.
   ```bash
    $ ./MolSim
  
    Usage: ./MolSim [-h | --help] | {-f | --filename} <filename> {-t | --t_end} <t_end> {-d | --delta_t} <delta_t> [-o | --output <output>] [-i | --iteration <iteration>] [-w | --writer {vtk | xyz}] [-p | --physics {gravitation | lennard}]
    Options:
          -h,--help               Show this help message
          -f,--filename           Specify the input filename
          -t,--t_end              Specify the end time of this simulation
          -d,--delta_t            Specify the time steps per calculation
          -o,--output             Specify the output filename
          -i,--iteration          Specify the iteration
          -w,--writer             Specify the writer used for the output files
          -p,--physics            Specify the physics used for the simulation

    Usage: ./MolSim [-x | --xml] {-f | --filename <filename>}
    Options:
          -f,--filename           Specify the input filename as xml

   ```

#### Worksheet 1:

- Run example simulation.
   ```bash
   $ ./MolSim --filename ../../input/eingabe-sonne.txt --t_end 1000 --delta_t 0.014 --physics gravitation
   ```
- _(optional)_ Run additional simulation of the solar system.
   ```bash
   $ ./MolSim -f ../../input/sun_system.txt -t 1000 -d 0.014 --p gravitation
   ```

#### Worksheet 2:

- Run example simulation.
   ```bash
   $ ./MolSim -x -f ../../input/input_task_3.xml
   ```

### Tests

- Run tests to verify correctness:
    ```bash
    $ ctest
    [...]
    100% tests passed, 0 tests failed out of x

    Total Test time (real) =   x sec
    ```

### Input file format

- XSD:
    ```xml
    <?xml version="1.0"?>
    <xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema">
        <xsd:complexType name="cuboid_t">
            <xsd:sequence>
                <xsd:element name="Position" type="vector_t"/>
                <xsd:element name="Velocity" type="vector_t"/>
                <xsd:element name="Dimension" type="vector_i"/>
            </xsd:sequence>
            <xsd:attribute name="distance" type="xsd:double" use="required"/>
            <xsd:attribute name="mass" type="xsd:double" use="required"/>
            <xsd:attribute name="meanValue" type="xsd:double" use="required"/>
        </xsd:complexType>
    
        <xsd:complexType name="sphere_t">
            <xsd:sequence>
                <xsd:element name="Center" type="vector_t"/>
                <xsd:element name="Velocity" type="vector_t"/>
            </xsd:sequence>
            <xsd:attribute name="radius" type="xsd:nonNegativeInteger" use="required"/>
            <xsd:attribute name="distance" type="xsd:double" use="required"/>
            <xsd:attribute name="mass" type="xsd:double" use="required"/>
            <xsd:attribute name="meanValue" type="xsd:double" use="required"/>
        </xsd:complexType>
    
        <xsd:complexType name="vector_t">
            <xsd:attribute name="x" type="xsd:double" use="required"/>
            <xsd:attribute name="y" type="xsd:double" use="required"/>
            <xsd:attribute name="z" type="xsd:double" use="required"/>
        </xsd:complexType>
    
        <xsd:complexType name="vector_i">
            <xsd:attribute name="x" type="xsd:nonNegativeInteger" use="required"/>
            <xsd:attribute name="y" type="xsd:nonNegativeInteger" use="required"/>
            <xsd:attribute name="z" type="xsd:nonNegativeInteger" use="required"/>
        </xsd:complexType>
    
        <xsd:complexType name="input_t">
            <xsd:attribute name="location" type="xsd:string" use="required"/>
        </xsd:complexType>
    
        <xsd:complexType name="shape_t">
            <xsd:sequence>
                <xsd:element name="Cuboid" type="cuboid_t" minOccurs="0" maxOccurs="unbounded"/>
                <xsd:element name="Sphere" type="sphere_t" minOccurs="0" maxOccurs="unbounded"/>
            </xsd:sequence>
        </xsd:complexType>
    
        <xsd:complexType name="simulation_t">
            <xsd:sequence>
                <xsd:element name="Shapes" type="shape_t" minOccurs="0" maxOccurs="unbounded"/>
                <xsd:element name="Source" type="input_t" minOccurs="0" maxOccurs="unbounded"/>
            </xsd:sequence>
            <xsd:attribute name="endTime" type="xsd:double"/>
            <xsd:attribute name="deltaT" type="xsd:double"/>
            <xsd:attribute name="output" type="xsd:string"/>
            <xsd:attribute name="iteration" type="xsd:nonNegativeInteger"/>
            <xsd:attribute name="physics" type="xsd:string"/>
            <xsd:attribute name="writer" type="xsd:string"/>
        </xsd:complexType>
        <xsd:element name="Simulation" type="simulation_t"/>
    </xsd:schema>
    ```

- XML:
    ```xml
    
    <Simulation endTime="3" deltaT="0.0002" iteration="60" physics="lennard" writer="vtk" output="MD">
        <Shapes>
            <Cuboid mass="1.0" distance="1.1225" meanValue="0.0">
                <Position x="0.0" y="0.0" z="0.0"/>
                <Velocity x="0.0" y="0.0" z="0.0"/>
                <Dimension x="5" y="20" z="5"/>
            </Cuboid>
            <Sphere mass="3.0" distance="1.1225" meanValue="0" radius="10">
                <Center x="25" y="10" z="0"/>
                <Velocity x="-15" y="0" z="0"/>
            </Sphere>
        </Shapes>
    </Simulation>
    ```

### Additional Makefile commands

#### Project Makefile:

You need to perform the following commands in the top level `project` folder.

- Remove the `build` folder.
   ```bash
   $ make clean
   ```
- Remove and create the `build` folder.
   ```bash
   $ make create_folder
   ```

#### Build Makefile:

You need to perform the following commands in the `build` folder.

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

## Contributors

Our project is developed by Dominik, Janin and Nils as part of Group A.

## License

MolSim is released under the [MIT license](https://github.com/Dominik-Weinzierl/MolSim).