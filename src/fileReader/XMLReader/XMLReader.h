#pragma once

#include "arguments/argument/XMLArgument/XMLArgument.h"
#include "generator/GeneratorArguments/CuboidArgument.h"
#include "generator/GeneratorArguments/SphereArgument.h"
#include "template/input.h"
#include <memory>

/**
 * XMLReader class reads a xml file and and provides Argument(s) to create Particle(s) via Generator(s)
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class XMLReader {
 public:

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
    std::optional<std::array<int, dim>> domain = std::nullopt;
    std::optional<std::vector<BoundaryType>> boundaries = std::nullopt;
    std::optional<std::array<int, dim>> cellSize = std::nullopt;

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

    if (simulation->Strategy()->LinkedCell().present()) {
      strategy = std::string{"LinkedCell"};
      cutoffRadius = simulation->Strategy()->LinkedCell().get().cutoffRadius();
      domain = this->loadDomain();
      boundaries = this->loadBoundaries();
      cellSize = this->loadCellSize();
    }

    return std::make_unique<XMLArgument<dim>>(files, endTime, deltaT, fileName, writer, iteration, physics,
                                              this->loadCuboid(), this->loadSpheres(), strategy, cutoffRadius, domain,
                                              boundaries, cellSize);
  }
 private:

  Vector<dim> wrapVector_t(const vector_t &input) const{
    Vector<dim> temp{input.x(), input.y()};
    if (dim == 3) {
      temp[2] = input.z();
    }
    return temp;
  }

  std::array<int, dim> wrapVector_i(const vector_i &input) const{
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
        sphereArguments.emplace_back(wrapVector_t(pos), rad, wrapVector_t(vel), dis, mass, mean, pack);
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
        cuboidArguments.emplace_back(wrapVector_t(pos), wrapVector_i(dime), wrapVector_t(vel), dis, mass, mean, pack);
      }
    }

    return cuboidArguments;
  }

  std::optional<std::array<int, dim>> loadDomain() const {
    return wrapVector_i(simulation->Strategy()->LinkedCell().get().Domain());
  }

  std::optional<std::array<int, dim>> loadCellSize() const {
    return wrapVector_i(simulation->Strategy()->LinkedCell().get().CellSize());
  }

  [[nodiscard]] std::optional<std::vector<BoundaryType>> loadBoundaries() const;

  BoundaryType toBoundaryType(std::string &s) const {
    if (s == "outflow") {
      return Outflow;
    } else if (s == "reflecting") {
      return Reflecting;
    }
    return Outflow;
  }

  /**
   * Xml file provided in a usable way.
   */
  std::unique_ptr<simulation_t> simulation;
};



