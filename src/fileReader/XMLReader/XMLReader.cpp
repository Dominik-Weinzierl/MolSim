#include "XMLReader.h"

XMLReader::XMLReader(const std::string &path) {
  try {
    simulation = Simulation(path, xml_schema::flags::dont_validate);
  } catch (const xml_schema::exception &e) {
    throw std::invalid_argument("[ERROR] Invalid xml path");
  }

  auto test = simulation->Cuboid();
  auto deltaT = simulation->deltaT();
  auto entTime = simulation->endTime();
}

