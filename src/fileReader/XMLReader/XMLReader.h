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
    std::string algorithm{"DirectSum"};
    std::optional<double> cutoffRadius = std::nullopt;
    std::optional<std::array<int, dim>> domain = std::nullopt;
    std::optional<std::vector<std::string>> boundaries = std::nullopt;

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
      algorithm = std::string{"LinkedCell"};
      cutoffRadius = simulation->Strategy()->LinkedCell().get().cutoffRadius();
      domain = this->loadDomain();
      boundaries = this->loadBoundaries();
    }

    return std::make_unique<XMLArgument<dim>>(files, endTime, deltaT, fileName, writer, iteration, physics,
                                              this->loadCuboid(), this->loadSpheres(), algorithm, cutoffRadius, domain,
                                              boundaries);
  }
 private:
  /**
   * Used to load the SphereArgument(s) from the xml file.
   * @return std::vector<SphereArgument<dim>>
   */
  std::vector<SphereArgument<dim>> loadSpheres() const;

  /**
   * Used to load the CuboidArgument(s) from the xml file.
   * @return std::vector<CuboidArgument<dim>>
   */
  std::vector<CuboidArgument<dim>> loadCuboid() const;

  std::optional<std::array<int, dim>> loadDomain() const;

  [[nodiscard]] std::optional<std::vector<std::string>> loadBoundaries() const;

  /**
   * Xml file provided in a usable way.
   */
  std::unique_ptr<simulation_t> simulation;
};



