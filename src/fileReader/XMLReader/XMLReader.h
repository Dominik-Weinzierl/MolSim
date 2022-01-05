#pragma once

#include <memory>

#include "arguments/argument/XMLArgument/XMLArgument.h"
#include "generator/GeneratorArguments/variants/CuboidArgument.h"
#include "generator/GeneratorArguments/SphereArgument.h"
#include "generator/GeneratorArguments/variants/MembraneArgument.h"
#include "template/input.h"
#include "thermostat/DummyThermostat.h"
#include "physics/Forces/Force.h"

/**
 * XMLReader class reads a xml file and and provides Argument(s) to create Particle(s) via Generator(s)
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class XMLReader {
 private:
  /**
   * Xml file provided in a usable way.
   */
  std::unique_ptr<simulation_t> simulation;

  //----------------------------------------Methods----------------------------------------

  Vector<dim> wrapVector_t(const vector_t &input) const {
    Vector<dim> temp{input.x(), input.y()};
    if (dim == 3) {
      temp[2] = input.z();
    }
    return temp;
  }

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
        int type = 0;
        if (sphere.type().present()) {
          type = static_cast<int>(sphere.type().get());
        }
        sphereArguments.emplace_back(wrapVector_t(pos), rad, wrapVector_t(vel), dis, mass, mean, pack, zeroCrossing,
                                     depthOfPotentialWell, type);
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
        int type = 0;
        if (cuboid.type().present()) {
          type = static_cast<int>(cuboid.type().get());
        }
        cuboidArguments
            .emplace_back(wrapVector_t(pos), wrapVector_i(dime), wrapVector_t(vel), dis, mass, mean, pack, zeroCrossing,
                          depthOfPotentialWell, type);
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
        int type = 0;
        if (membrane.type().present()) {
          type = static_cast<int>(membrane.type().get());
        }
        membraneArguments.template emplace_back(wrapVector_t(pos),
                                                wrapVector_i(dime),
                                                wrapVector_t(vel),
                                                dis,
                                                mass,
                                                mean,
                                                pack,
                                                zeroCrossing,
                                                depthOfPotentialWell,
                                                stiffness,
                                                averageBondLength,
                                                type);
      }
    }

    return membraneArguments;
  }

  std::optional<Vector<dim>> loadDomain() const {
    return wrapVector_t(simulation->Strategy()->LinkedCell().get().Domain());
  }

  std::optional<Vector<dim>> loadCellSize() const {
    return wrapVector_t(simulation->Strategy()->LinkedCell().get().CellSize());
  }

  [[nodiscard]] std::optional<std::vector<BoundaryType>> loadBoundaries() const;

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
    std::optional<Vector<dim>> additionalGravitation = std::nullopt;
    std::optional<std::vector<Force<dim>>> forces = std::nullopt;

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
    }

    if (simulation->Thermostat().present()) {
      double initialT = simulation->Thermostat()->initialT();
      double targetT =
          simulation->Thermostat()->targetT().present() ? simulation->Thermostat()->targetT().get() : initialT;
      int numberT = static_cast<int>(simulation->Thermostat()->numberT());
      int tDeltaT =
          simulation->Thermostat()->deltaT().present() ? static_cast<int>(simulation->Thermostat()->deltaT().get())
                                                       : -1;
      thermostat = std::make_unique<Thermostat<dim>>(initialT, targetT, numberT, tDeltaT);
    } else {
      thermostat = std::make_unique<DummyThermostat<dim>>();
    }

    if (simulation->AdditionalGravitation().present()) {
      additionalGravitation = wrapVector_t(simulation->AdditionalGravitation().get());
    }

    for (auto &i: simulation->Force()) {
      std::vector<Vector<dim>> indices{};

      if (!i.Index().empty()) {
        for (auto &j: i.Index()) {
          indices.template emplace_back({j.x(), j.y(), j.z()});
        }
      } else {
        //TODO: Können hier sonst iwelche unüberschriebene Werte liegen?
        indices.clear();
      }

      forces->template emplace_back(Force<dim>{indices, wrapVector_t({i.forceX(), i.forceY(), i.forceZ()}), i.start(), i.end()});
    }

    return std::make_unique<XMLArgument<dim>>(files,
                                              endTime,
                                              deltaT,
                                              fileName,
                                              writer,
                                              iteration,
                                              physics,
                                              this->loadCuboid(),
                                              this->loadSpheres(),
                                              this->loadMembrane(),
                                              strategy,
                                              cutoffRadius,
                                              domain,
                                              boundaries,
                                              cellSize,
                                              std::move(thermostat),
                                              additionalGravitation,
                                              forces);
  }
};
