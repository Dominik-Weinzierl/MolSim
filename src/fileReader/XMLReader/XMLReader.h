#pragma once

#include "arguments/argument/XMLArgument/XMLArgument.h"
#include "generator/GeneratorArguments/CuboidArgument.h"
#include "generator/GeneratorArguments/SphereArgument.h"
#include "template/input.h"
#include <memory>

template<size_t dim>
class XMLReader {
 public:
  explicit XMLReader(const std::string &path) {
    try {
      simulation = Simulation(path, xml_schema::flags::dont_validate);
    } catch (const xml_schema::exception &e) {
      throw std::invalid_argument("[ERROR] " + std::string{e.what()});
    }
  }

  [[nodiscard]] std::unique_ptr<XMLArgument<dim>> readXML() {
    std::vector<std::string> files;
    std::string physics{"default"};
    std::string writer{"default"};
    double endTime = -1;
    double deltaT = -1;
    int iteration = -1;
    std::string fileName = "default";

    for (auto &it: simulation->Source()) {
      std::string path = it.location();
      files.push_back(path);
    }

    if (simulation->physics().present()) {
      physics = simulation->physics().get();
    }
    if (simulation->writer().present()) {
      writer = simulation->writer().get();
    }
    if (simulation->endTime().present()) {
      endTime = simulation->endTime().get();
    }
    if (simulation->deltaT().present()) {
      deltaT = simulation->deltaT().get();
    }
    if (simulation->output().present()) {
      fileName = simulation->output().get();
    }
    if (simulation->iteration().present()) {
      iteration = static_cast<int>(simulation->iteration().get());
    }

    return std::make_unique<XMLArgument<dim>>(this->loadCuboid(), this->loadSpheres(), files, endTime, deltaT, fileName,
                                              writer, iteration, physics);
  }
 private:
  std::vector<SphereArgument<dim>> loadSpheres() const;
  std::vector<CuboidArgument<dim>> loadCuboid() const;
  std::unique_ptr<simulation_t> simulation;
};



