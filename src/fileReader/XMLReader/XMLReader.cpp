#include "XMLReader.h"

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
      auto &pack = sphere.packed();
      Vector<3> position{pos.x(), pos.y(), pos.z()};
      Vector<3> velocity{vel.x(), vel.y(), vel.z()};
      sphereArguments.emplace_back(position, rad, velocity, dis, mass, mean, pack);
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
      auto &pack = sphere.packed();
      Vector<2> position{pos.x(), pos.y()};
      Vector<2> velocity{vel.x(), vel.y()};
      sphereArguments.emplace_back(position, rad, velocity, dis, mass, mean, pack);
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
      auto &pack = cuboid.packed();
      Vector<3> position{pos.x(), pos.y(), pos.z()};
      std::vector<int> dimension{static_cast<int>(dime.x()), static_cast<int>(dime.y()), static_cast<int>(dime.z())};
      Vector<3> velocity{vel.x(), vel.y(), vel.z()};
      cuboidArguments.emplace_back(position, dimension, velocity, dis, mass, mean, pack);
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
      auto &pack = cuboid.packed();
      Vector<2> position{pos.x(), pos.y()};
      std::vector<int> dimension{static_cast<int>(dime.x()), static_cast<int>(dime.y())};
      Vector<2> velocity{vel.x(), vel.y()};
      cuboidArguments.emplace_back(position, dimension, velocity, dis, mass, mean, pack);
    }
  }

  return cuboidArguments;
}

template<>
std::optional<std::array<int, 3>> XMLReader<3>::loadDomain() const {
  auto dom = simulation->Strategy()->LinkedCell().get().Domain();
  return std::array<int, 3>{static_cast<int>(dom.x()), static_cast<int>(dom.y()), static_cast<int>(dom.z())};
}

template<>
std::optional<std::array<int, 2>> XMLReader<2>::loadDomain() const {
  auto dom = simulation->Strategy()->LinkedCell().get().Domain();
  return std::array<int, 2>{static_cast<int>(dom.x()), static_cast<int>(dom.y())};
}

template<>
std::optional<std::vector<std::string>> XMLReader<3>::loadBoundaries() const {
  auto linked = simulation->Strategy()->LinkedCell().get();

  if (linked.Boundary().boundary().present()) {
    return std::vector<std::string>(6, linked.Boundary().boundary().get());
  }
  std::vector<std::string> bounds(6, "outflow");

  if (linked.Boundary().boundary_right().present()) {
    bounds[0] = linked.Boundary().boundary_right().get();
  }

  if (linked.Boundary().boundary_left().present()) {
    bounds[1] = linked.Boundary().boundary_left().get();
  }

  if (linked.Boundary().boundary_top().present()) {
    bounds[2] = linked.Boundary().boundary_top().get();
  }

  if (linked.Boundary().boundary_bottom().present()) {
    bounds[3] = linked.Boundary().boundary_bottom().get();
  }

  if (linked.Boundary().boundary_back().present()) {
    bounds[4] = linked.Boundary().boundary_back().get();
  }

  if (linked.Boundary().boundary_front().present()) {
    bounds[5] = linked.Boundary().boundary_front().get();
  }

  return bounds;
}

template<>
std::optional<std::vector<std::string>> XMLReader<2>::loadBoundaries() const {
  auto linked = simulation->Strategy()->LinkedCell().get();

  if (linked.Boundary().boundary().present()) {
    return std::vector<std::string>(4, linked.Boundary().boundary().get());
  }
  std::vector<std::string> bounds(4, "outflow");

  if (linked.Boundary().boundary_right().present()) {
    bounds[0] = linked.Boundary().boundary_right().get();
  }

  if (linked.Boundary().boundary_left().present()) {
    bounds[1] = linked.Boundary().boundary_left().get();
  }

  if (linked.Boundary().boundary_top().present()) {
    bounds[2] = linked.Boundary().boundary_top().get();
  }

  if (linked.Boundary().boundary_bottom().present()) {
    bounds[3] = linked.Boundary().boundary_bottom().get();
  }

  return bounds;
}



