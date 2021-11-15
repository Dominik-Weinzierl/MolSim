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
      throw std::invalid_argument("[ERROR] " + std::string{e.what()});
    }
  }

  /**
   * Reads the provided xml file and creates an XMLArgument.
   * @return std::unique_ptr<XMLArgument<dim>>
   */
  [[nodiscard]] std::unique_ptr<XMLArgument<dim>> readXML() {
    std::vector<std::string> files;
    std::string physics{"gravitation"};
    std::string writer{"vtk"};
    double endTime = 1000;
    double deltaT = 0.0002;
    int iteration = 60;
    std::string fileName = "MD";

    for (auto &it: simulation->Source()) {
      std::string path = it.location();
      files.push_back(path);
    }

    if (simulation->physics().present()) {
      physics = simulation->physics().get(); // NOLINT(cppcoreguidelines-slicing)
    }
    if (simulation->writer().present()) {
      writer = simulation->writer().get(); // NOLINT(cppcoreguidelines-slicing)
    }
    if (simulation->endTime().present()) {
      endTime = simulation->endTime().get();
    }
    if (simulation->deltaT().present()) {
      deltaT = simulation->deltaT().get();
    }
    if (simulation->output().present()) {
      fileName = simulation->output().get(); // NOLINT(cppcoreguidelines-slicing)
    }
    if (simulation->iteration().present()) {
      iteration = static_cast<int>(simulation->iteration().get());
    }

    return std::make_unique<XMLArgument<dim>>(this->loadCuboid(), this->loadSpheres(), files, endTime, deltaT, fileName,
                                              writer, iteration, physics);
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

  /**
   * Xml file provided in a usable way.
   */
  std::unique_ptr<simulation_t> simulation;
};



