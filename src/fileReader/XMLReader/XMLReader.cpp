#include "XMLReader.h"

template<>
std::optional<std::vector<BoundaryType>> XMLReader<3>::loadBoundaries() const {
  auto linked = simulation->Strategy()->LinkedCell().get();

  if (linked.Boundary().boundary().present()) {
    return std::vector<BoundaryType>(6, toBoundaryType(linked.Boundary().boundary().get()));
  }
  std::vector<BoundaryType> bounds(6, BoundaryType::Outflow);

  if (linked.Boundary().boundary_right().present()) {
    bounds[0] = toBoundaryType(linked.Boundary().boundary_right().get());
  }

  if (linked.Boundary().boundary_left().present()) {
    bounds[1] = toBoundaryType(linked.Boundary().boundary_left().get());
  }

  if (linked.Boundary().boundary_top().present()) {
    bounds[2] = toBoundaryType(linked.Boundary().boundary_top().get());
  }

  if (linked.Boundary().boundary_bottom().present()) {
    bounds[3] = toBoundaryType(linked.Boundary().boundary_bottom().get());
  }

  if (linked.Boundary().boundary_back().present()) {
    bounds[4] = toBoundaryType(linked.Boundary().boundary_back().get());
  }

  if (linked.Boundary().boundary_front().present()) {
    bounds[5] = toBoundaryType(linked.Boundary().boundary_front().get());
  }

  return bounds;
}

template<>
std::optional<std::vector<BoundaryType>> XMLReader<2>::loadBoundaries() const {
  auto linked = simulation->Strategy()->LinkedCell().get();

  if (linked.Boundary().boundary().present()) {
    return std::vector<BoundaryType>(4, toBoundaryType(linked.Boundary().boundary().get()));
  }
  std::vector<BoundaryType> bounds(4, BoundaryType::Outflow);

  if (linked.Boundary().boundary_right().present()) {
    bounds[0] = toBoundaryType(linked.Boundary().boundary_right().get());
  }

  if (linked.Boundary().boundary_left().present()) {
    bounds[1] = toBoundaryType(linked.Boundary().boundary_left().get());
  }

  if (linked.Boundary().boundary_top().present()) {
    bounds[2] = toBoundaryType(linked.Boundary().boundary_top().get());
  }

  if (linked.Boundary().boundary_bottom().present()) {
    bounds[3] = toBoundaryType(linked.Boundary().boundary_bottom().get());
  }

  return bounds;
}



