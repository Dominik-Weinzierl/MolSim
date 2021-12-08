#include <gtest/gtest.h>

#include "arguments/argument/XMLArgument/XMLArgument.h"

/**
 * ***************************************************
 * Test correct functionality of the class XMLArgument.
 * ******************************************+********
 */

/**
* Test that constructor sets all values as expected.
*/
TEST(XMLArgument_3D, constructor) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  std::vector<std::string> files{"files"};
  double endTime = 5.0;
  double deltaT = 0.002;
  std::string output{"output"};
  std::string writer{"vtk"};
  int iteration = 5;
  std::string physics{"gravitation"};
  std::vector<CuboidArgument<dim>>
      cuboidArguments{CuboidArgument<dim>{{0, 0, 0}, {40, 8, 1}, {0, 0, 0}, 1.1225, 1.0, 0.1, true}};
  std::vector<SphereArgument<dim>>
      sphereArguments{SphereArgument<dim>{{15.0, 15.0, 0}, 3, {0, -10, 0}, 1.1225, 1.0, 0.1, true}};
  std::string strategy{"DirectSum"};
  std::optional<double> cutoffRadius{5.0};
  std::optional<std::array<int, dim>> domain{{5, 5, 5}};
  std::optional<std::vector<BoundaryType>> boundaries
      {{BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Reflecting, BoundaryType::Reflecting,
        BoundaryType::Outflow, BoundaryType::Outflow}};
  std::optional<std::array<int, dim>> cellSize{{1, 1, 1}};

  XMLArgument<dim> arg
      {files, endTime, deltaT, output, writer, iteration, physics, cuboidArguments, sphereArguments, strategy,
       cutoffRadius, domain, boundaries, cellSize};

  // Expect getter und setter to return correct values
  EXPECT_EQ(arg.getFiles(), files);
  EXPECT_EQ(arg.getEndTime(), endTime);
  EXPECT_EQ(arg.getDeltaT(), deltaT);
  EXPECT_EQ(arg.getOutput(), output);
  EXPECT_EQ(arg.getWriter(), writer);
  EXPECT_EQ(arg.getIteration(), iteration);
  EXPECT_EQ(arg.getPhysics(), physics);
  EXPECT_EQ(arg.getCuboidArguments(), cuboidArguments);
  EXPECT_EQ(arg.getSphereArguments(), sphereArguments);
  EXPECT_EQ(arg.getStrategy(), strategy);
  EXPECT_EQ(arg.getCutoffRadius(), cutoffRadius);
  EXPECT_EQ(arg.getDomain(), domain);
  EXPECT_EQ(arg.getBoundaries(), boundaries);
  EXPECT_EQ(arg.getCellSize(), cellSize);
}

/**
* Test that constructor sets all values as expected.
*/
TEST(XMLArgument_2D, constructor) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  std::vector<std::string> files{"files"};
  double endTime = 5.0;
  double deltaT = 0.002;
  std::string output{"output"};
  std::string writer{"vtk"};
  int iteration = 5;
  std::string physics{"gravitation"};
  std::vector<CuboidArgument<dim>>
      cuboidArguments{CuboidArgument<dim>{{0, 0}, {40, 8}, {0, 0}, 1.1225, 1.0, 0.1, true}};
  std::vector<SphereArgument<dim>>
      sphereArguments{SphereArgument<dim>{{15.0, 15.0}, 3, {0, -10}, 1.1225, 1.0, 0.1, true}};
  std::string strategy{"DirectSum"};
  std::optional<double> cutoffRadius{5.0};
  std::optional<std::array<int, dim>> domain{{5, 5}};
  std::optional<std::vector<BoundaryType>>
      boundaries{{BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Reflecting, BoundaryType::Reflecting}};
  std::optional<std::array<int, dim>> cellSize{{1, 1}};

  XMLArgument<dim> arg
      {files, endTime, deltaT, output, writer, iteration, physics, cuboidArguments, sphereArguments, strategy,
       cutoffRadius, domain, boundaries, cellSize};

  // Expect getter und setter to return correct values
  EXPECT_EQ(arg.getFiles(), files);
  EXPECT_EQ(arg.getEndTime(), endTime);
  EXPECT_EQ(arg.getDeltaT(), deltaT);
  EXPECT_EQ(arg.getOutput(), output);
  EXPECT_EQ(arg.getWriter(), writer);
  EXPECT_EQ(arg.getIteration(), iteration);
  EXPECT_EQ(arg.getPhysics(), physics);
  EXPECT_EQ(arg.getCuboidArguments(), cuboidArguments);
  EXPECT_EQ(arg.getSphereArguments(), sphereArguments);
  EXPECT_EQ(arg.getStrategy(), strategy);
  EXPECT_EQ(arg.getCutoffRadius(), cutoffRadius);
  EXPECT_EQ(arg.getDomain(), domain);
  EXPECT_EQ(arg.getBoundaries(), boundaries);
  EXPECT_EQ(arg.getCellSize(), cellSize);
}

/**
* Test that the compare operator works as expected and both arguments are equal.
*/
TEST(XMLArgument, compareOperatorEqual) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  std::vector<std::string> files{"files"};
  double endTime = 5.0;
  double deltaT = 0.002;
  std::string output{"output"};
  std::string writer{"vtk"};
  int iteration = 5;
  std::string physics{"gravitation"};
  std::vector<CuboidArgument<dim>> cuboidArguments{};
  std::vector<SphereArgument<dim>> sphereArguments{};
  std::string strategy{"DirectSum"};
  std::optional<double> cutoffRadius{5.0};
  std::optional<std::array<int, dim>> domain{{5, 5}};
  std::optional<std::vector<BoundaryType>> boundaries{};
  std::optional<std::array<int, dim>> cellSize{{1, 1}};

  XMLArgument<dim> first
      {files, endTime, deltaT, output, writer, iteration, physics, cuboidArguments, sphereArguments, strategy,
       cutoffRadius, domain, boundaries, cellSize};

  XMLArgument<dim> second = first;

  EXPECT_EQ(first, second);
}

/**
* Test that the compare operator works as expected and both arguments are not equal
*/
TEST(XMLArgument, compareOperatorNotEqual) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  std::vector<std::string> files{"files"};
  double endTime = 5.0;
  double deltaT = 0.002;
  std::string output{"output"};
  std::string writer{"vtk"};
  int iteration = 5;
  std::string physics{"gravitation"};
  std::vector<CuboidArgument<dim>> cuboidArguments{};
  std::vector<SphereArgument<dim>> sphereArguments{};
  std::string strategy{"DirectSum"};
  std::optional<double> cutoffRadius{5.0};
  std::optional<std::array<int, dim>> domain{{5, 5}};
  std::optional<std::vector<BoundaryType>> boundaries{};
  std::optional<std::array<int, dim>> cellSize{{1, 1}};

  XMLArgument<dim> first
      {files, endTime, deltaT, output, writer, iteration, physics, cuboidArguments, sphereArguments, strategy,
       cutoffRadius, domain, boundaries, cellSize};

  physics = std::string{"lennard"};

  XMLArgument<dim> second
      {files, endTime, deltaT, output, writer, iteration, physics, cuboidArguments, sphereArguments, strategy,
       cutoffRadius, domain, boundaries, cellSize};

  EXPECT_NE(first, second);
}
