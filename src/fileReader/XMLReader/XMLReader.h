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

template<>
std::vector<SphereArgument<3>> XMLReader<3>::loadSpheres() const {
  std::vector<SphereArgument<3>> sphereArguments;

  for (auto &it: simulation->Shapes()) {
    for (auto &sphere: it.Sphere()) {
      auto &pos = sphere.Center();
      auto &rad = sphere.radius();
      auto &vel = sphere.Velocity();
      auto &dis = sphere.distance();
      auto &mass = sphere.mass();
      auto &mean = sphere.meanValue();
      Vector<3> position{pos.x(), pos.y(), pos.z()};
      Vector<3> velocity{vel.x(), vel.y(), vel.z()};
      sphereArguments.emplace_back(position, rad, velocity, dis, mass, mean);
    }
  }

  return sphereArguments;
}

template<>
std::vector<SphereArgument<2>> XMLReader<2>::loadSpheres() const {
  std::vector<SphereArgument<2>> sphereArguments;

  for (auto &it: simulation->Shapes()) {
    for (auto &sphere: it.Sphere()) {
      auto &pos = sphere.Center();
      auto &rad = sphere.radius();
      auto &vel = sphere.Velocity();
      auto &dis = sphere.distance();
      auto &mass = sphere.mass();
      auto &mean = sphere.meanValue();
      Vector<2> position{pos.x(), pos.y()};
      Vector<2> velocity{vel.x(), vel.y()};
      sphereArguments.emplace_back(position, rad, velocity, dis, mass, mean);
    }
  }

  return sphereArguments;
}

template<>
std::vector<CuboidArgument<3>> XMLReader<3>::loadCuboid() const {
  std::vector<CuboidArgument<3>> cuboidArguments;

  for (auto &it: simulation->Shapes()) {
    for (auto &cuboid: it.Cuboid()) {
      auto &pos = cuboid.Position();
      auto &dime = cuboid.Dimension();
      auto &vel = cuboid.Velocity();
      auto &dis = cuboid.distance();
      auto &mass = cuboid.mass();
      auto &mean = cuboid.meanValue();
      Vector<3> position{pos.x(), pos.y(), pos.z()};
      std::vector<int> dimension{static_cast<int>(dime.x()), static_cast<int>(dime.y()), static_cast<int>(dime.z())};
      Vector<3> velocity{vel.x(), vel.y(), vel.z()};
      cuboidArguments.emplace_back(position, dimension, velocity, dis, mass, mean);
    }
  }

  return cuboidArguments;
}

template<>
std::vector<CuboidArgument<2>> XMLReader<2>::loadCuboid() const {
  std::vector<CuboidArgument<2>> cuboidArguments;

  for (auto &it: simulation->Shapes()) {
    for (auto &cuboid: it.Cuboid()) {
      auto &pos = cuboid.Position();
      auto &dime = cuboid.Dimension();
      auto &vel = cuboid.Velocity();
      auto &dis = cuboid.distance();
      auto &mass = cuboid.mass();
      auto &mean = cuboid.meanValue();
      Vector<2> position{pos.x(), pos.y()};
      std::vector<int> dimension{static_cast<int>(dime.x()), static_cast<int>(dime.y())};
      Vector<2> velocity{vel.x(), vel.y()};
      cuboidArguments.emplace_back(position, dimension, velocity, dis, mass, mean);
    }
  }

  return cuboidArguments;
}



