#include <generator/GeneratorArguments/CuboidArgument.h>
#include "XMLReader.h"

XMLReader::XMLReader(const std::string &path) {
  try {
    simulation = Simulation(path, xml_schema::flags::dont_validate);
  } catch (const xml_schema::exception &e) {
    throw std::invalid_argument("[ERROR] " + std::string{e.what()});
  }
}

std::unique_ptr<XMLArgument> XMLReader::readXML() const {
  std::vector<CuboidArgument> cuboidArguments;
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

  for (auto &it: simulation->Cuboid()) {
    auto &pos = it.Position();
    auto &dim = it.Dimension();
    auto &vel = it.Velocity();
    auto &dis = it.distance();
    auto &mass = it.mass();
    auto &mean = it.meanValue();
    Vector<> position{pos.x(), pos.y(), pos.z()};
    std::vector<int> dimension{static_cast<int>(dim.x()), static_cast<int>(dim.y()), static_cast<int>(dim.z())};
    Vector<> velocity{vel.x(), vel.y(), vel.z()};
    cuboidArguments.emplace_back(position, dimension, velocity, dis, mass, mean);
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

  return std::make_unique<XMLArgument>(cuboidArguments, files, endTime, deltaT, fileName, writer, iteration, physics);
}

