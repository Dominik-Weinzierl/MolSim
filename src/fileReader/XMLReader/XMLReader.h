#pragma once

#include <memory>

#include "arguments/argument/XMLArgument/XMLArgument.h"
#include "generator/GeneratorArguments/variants/CuboidArgument.h"
#include "generator/GeneratorArguments/SphereArgument.h"
#include "generator/GeneratorArguments/variants/MembraneArgument.h"
#include "template/input.h"
#include "thermostat/DummyThermostat.h"
#include "physics/Forces/ForceContainer.h"
#include "thermostat/FlowThermostat.h"
#include "outputWriter/ProfileWriter/ProfileWriter.h"

/**
 * XMLReader class reads a xml file and and provides Argument(s) to create Particle(s) via Generator(s)
 * @tparam dim dimension of our simulation
 */
template<size_t dim>
class XMLReader {
 private:
  /**
   * Xml file provided in a usable way.
   */
  std::unique_ptr<simulation_t> simulation;

  //----------------------------------------Methods----------------------------------------

  /**
   * Generates Vector out of xsd vector_t.
   * @param input xsd vector_t
   * @return Vector
   */
  Vector<dim> wrapVector_t(const vector_t &input) const {
    Vector<dim> temp{input.x(), input.y()};
    if (dim == 3) {
      temp[2] = input.z();
    }
    return temp;
  }

  /**
   * Generates Vector out of xsd vector_i.
   * @param input xsd vector_i
   * @return Vector
   */
  std::array<int, dim> wrapVector_i(const vector_i &input) const {
    std::array<int, dim> temp{static_cast<int>(input.x()), static_cast<int>(input.y())};
    if (dim == 3) {
      temp[2] = static_cast<int>(input.z());
    }
    return temp;
  }

  /**
   * Used to load the SphereArgument(s) from the xml file.
   * @return std::vector<SphereArgument<dim>>
   */
  std::vector<SphereArgument<dim>> loadSpheres() const {
    std::vector<SphereArgument<dim>> sphereArguments;

    for (auto &it: simulation->Shapes()) {
      for (auto &sphere: it.Sphere()) {
        auto &pos = sphere.Center();
        auto &rad = sphere.radius();
        auto &vel = sphere.Velocity();
        auto &dis = sphere.distance();
        auto &mass = sphere.mass();
        auto &mean = sphere.meanValue();
        auto &pack = sphere.packed();
        auto &zeroCrossing = sphere.zeroCrossing();
        auto &depthOfPotentialWell = sphere.depthOfPotentialWell();

        std::vector<ForceContainer<dim>> forces;
        for (auto &f: sphere.Forces()) {
          forces.push_back(loadForces(f));
        }

        int type = 0;
        if (sphere.type().present()) {
          type = static_cast<int>(sphere.type().get());
        }
        bool fixed = false;
        if (sphere.fixed().present()) {
          fixed = sphere.fixed().get();
        }
        sphereArguments.emplace_back(wrapVector_t(pos), rad, wrapVector_t(vel), dis, mass, mean, pack, zeroCrossing,
                                     depthOfPotentialWell, type, fixed, forces);
      }
    }

    return sphereArguments;
  }

  /**
   * Used to load the CuboidArgument(s) from the xml file.
   * @return std::vector<CuboidArgument<dim>>
   */
  std::vector<CuboidArgument<dim>> loadCuboid() const {
    std::vector<CuboidArgument<dim>> cuboidArguments;

    for (auto &it: simulation->Shapes()) {
      for (auto &cuboid: it.Cuboid()) {
        auto &pos = cuboid.Position();
        auto &dime = cuboid.Dimension();
        auto &vel = cuboid.Velocity();
        auto &dis = cuboid.distance();
        auto &mass = cuboid.mass();
        auto &mean = cuboid.meanValue();
        auto &pack = cuboid.packed();
        auto &zeroCrossing = cuboid.zeroCrossing();
        auto &depthOfPotentialWell = cuboid.depthOfPotentialWell();

        std::vector<ForceContainer<dim>> forces;
        for (auto &f: cuboid.Forces()) {
          forces.push_back(loadForces(f));
        }

        int type = 0;
        if (cuboid.type().present()) {
          type = static_cast<int>(cuboid.type().get());
        }
        bool fixed = false;
        if (cuboid.fixed().present()) {
          fixed = cuboid.fixed().get();
        }
        cuboidArguments
            .emplace_back(wrapVector_t(pos), wrapVector_i(dime), wrapVector_t(vel), dis, mass, mean, pack, zeroCrossing,
                          depthOfPotentialWell, type, fixed, forces);
      }
    }

    return cuboidArguments;
  }

  /**
   * Used to load the MembraneArgument(s) from the xml file.
   * @return std::vector<MembraneArgument<dim>>
   */
  std::vector<MembraneArgument<dim>> loadMembrane() const {

    std::vector<MembraneArgument<dim>> membraneArguments;

    for (auto &it: simulation->Shapes()) {
      for (auto &membrane: it.Membrane()) {
        auto &pos = membrane.Position();
        auto &dime = membrane.Dimension();
        auto &vel = membrane.Velocity();
        auto &dis = membrane.distance();
        auto &mass = membrane.mass();
        auto &mean = membrane.meanValue();
        auto &pack = membrane.packed();
        auto &zeroCrossing = membrane.zeroCrossing();
        auto &depthOfPotentialWell = membrane.depthOfPotentialWell();
        auto &stiffness = membrane.stiffness();
        auto &averageBondLength = membrane.averageBondLength();

        auto fixedOutline = false;
        if (membrane.fixedOutline().present()) {
          fixedOutline = membrane.fixedOutline();
        }

        std::vector<ForceContainer<dim>> forces;
        for (auto &f: membrane.Forces()) {
          forces.push_back(loadForces(f));
        }

        int type = 0;
        if (membrane.type().present()) {
          type = static_cast<int>(membrane.type().get());
        }
        bool fixed = false;
        if (membrane.fixed().present()) {
          fixed = membrane.fixed().get();
        }
        membraneArguments
            .template emplace_back(wrapVector_t(pos), wrapVector_i(dime), wrapVector_t(vel), dis, mass, mean, pack,
                                   zeroCrossing, depthOfPotentialWell, stiffness, averageBondLength, type, fixed,
                                   forces, fixedOutline);
      }
    }

    return membraneArguments;
  }

  /**
   * Loads the Domain from the xml file.
   * @return std::optional<Vector<dim>>
   */
  std::optional<Vector<dim>> loadDomain() const {
    return wrapVector_t(simulation->Strategy()->LinkedCell().get().Domain());
  }

  /**
   * Loads the CellSize from the xml file.
   * @return std::optional<Vector<dim>>
   */
  std::optional<Vector<dim>> loadCellSize() const {
    return wrapVector_t(simulation->Strategy()->LinkedCell().get().CellSize());
  }

  /**
   * Loads the Force(s) from the xml file.
   * @param force xsd force_t
   * @return ForceContainer<dim>
   */
  ForceContainer<dim> loadForces(force_t &force) const {
    std::vector<std::array<int, dim>> indices{};
    for (auto &j: force.Index()) {
      indices.push_back(wrapVector_i(j));
    }
    return ForceContainer<dim>{indices, wrapVector_t(force.Strength()), static_cast<unsigned int>(force.start()),
                               static_cast<unsigned int>(force.end())};
  }

  /**
   * Loads the boundaries from the xml file.
   * @return std::optional<std::vector<BoundaryType>>
   */
  [[nodiscard]] std::optional<std::vector<BoundaryType>> loadBoundaries() const;

  /**
   * Converts a given string to a BoundaryType. This step is needed since we only accept values of the enum
   * BoundaryType in our Simulation.
   * @param s String to convert to BoundaryType
   * @return BoundaryType
   */
  BoundaryType toBoundaryType(std::string &s) const {
    if (s == "outflow") {
      return Outflow;
    } else if (s == "reflecting") {
      return Reflecting;
    } else if (s == "periodic") {
      return Periodic;
    }
    return Outflow;
  }

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * Reads the provided xml file and verifies the format.
   * @param path xml file path
   */
  explicit XMLReader(const std::string &path) {
    try {
      simulation = Simulation(path, xml_schema::flags::dont_validate);
    } catch (const xml_schema::exception &e) {
      throw std::invalid_argument(std::string{e.what()});
    }
  }

  //----------------------------------------Methods----------------------------------------

  /**
   * Reads the provided xml file and creates an XMLArgument.
   * @return std::unique_ptr<XMLArgument<dim>>
   */
  [[nodiscard]] std::unique_ptr<XMLArgument<dim>> readXML() {
    std::vector<std::string> files;
    std::string physics;
    std::string writer;
    double endTime;
    double deltaT;
    int iteration;
    std::string fileName;
    std::string strategy{"DirectSum"};
    std::optional<double> cutoffRadius = std::nullopt;
    std::optional<Vector<dim>> domain = std::nullopt;
    std::optional<std::vector<BoundaryType>> boundaries = std::nullopt;
    std::optional<Vector<dim>> cellSize = std::nullopt;
    std::unique_ptr<Thermostat<dim>> thermostat;
    std::unique_ptr<ProfileWriter<dim>> profileWriter;
    std::optional<std::string> parallel = std::nullopt;
    Vector<dim> additionalGravitation{};
    std::vector<ForceContainer<dim>> forces{};

    for (auto &it: simulation->Source()) {
      std::string path = it.path();
      files.push_back(path);
    }

    physics = simulation->physics();
    writer = simulation->writer();
    endTime = simulation->endTime();
    deltaT = simulation->deltaT();
    fileName = simulation->output();
    iteration = static_cast<int>(simulation->iteration());

    if (simulation->Strategy().present() && simulation->Strategy()->LinkedCell().present()) {
      strategy = std::string{"LinkedCell"};
      cutoffRadius = simulation->Strategy()->LinkedCell().get().cutoffRadius();
      domain = this->loadDomain();
      boundaries = this->loadBoundaries();
      cellSize = this->loadCellSize();
      if (simulation->Strategy()->LinkedCell()->parallel().present()) {
        parallel = simulation->Strategy()->LinkedCell()->parallel().get();
      }
    }

    if (simulation->Thermostat().present()) {
      double initialT = simulation->Thermostat()->initialT();
      double targetT =
          simulation->Thermostat()->targetT().present() ? simulation->Thermostat()->targetT().get() : initialT;
      int numberT = static_cast<int>(simulation->Thermostat()->numberT());
      int tDeltaT =
          simulation->Thermostat()->deltaT().present() ? static_cast<int>(simulation->Thermostat()->deltaT().get())
                                                       : -1;
      if (simulation->Thermostat()->flow().present() && simulation->Thermostat()->flow().get())
        thermostat = std::make_unique<FlowThermostat<dim>>(initialT, targetT, numberT, tDeltaT);
      else
        thermostat = std::make_unique<Thermostat<dim>>(initialT, targetT, numberT, tDeltaT);
    } else {
      thermostat = std::make_unique<DummyThermostat<dim>>();
    }

    std::string path{"output/"};
    
    // we can't really generate the profiles if using direct sum, as the domain size is not known a priori.
    if (simulation->ProfileWriter().present() && strategy == "LinkedCell") {
      if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
      }
      path += fileName;
      int numOfBins = static_cast<int>(simulation->ProfileWriter()->numOfBins());
      int numOfIterations = static_cast<int>(simulation->ProfileWriter()->numOfIterations());
      bool velocity = simulation->ProfileWriter()->velocity();
      bool density = simulation->ProfileWriter()->density();
      profileWriter =
          std::make_unique<ProfileWriter<dim>>(numOfBins, numOfIterations, velocity, density, *domain, path);
    } else {
      profileWriter = std::make_unique<DummyProfileWriter<dim>>();
    }

    if (simulation->AdditionalGravitation().present()) {
      additionalGravitation = wrapVector_t(simulation->AdditionalGravitation().get());
    }

    return std::make_unique<XMLArgument<dim>>(files, endTime, deltaT, fileName, writer, iteration, physics,
                                              this->loadCuboid(), this->loadSpheres(), this->loadMembrane(), strategy,
                                              cutoffRadius, domain, boundaries, cellSize, std::move(thermostat),
                                              std::move(profileWriter), additionalGravitation, parallel);
  }
};
