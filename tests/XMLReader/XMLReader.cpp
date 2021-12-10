#include <gtest/gtest.h>

#include "fileReader/XMLReader/XMLReader.h"

/**
 * ***************************************************
 * Test correct functionality of the class XMLReader.
 * ******************************************+********
 */

/**
* Test that all fields of the XMLArgument are set correctly for test_case_1.xml for 3d simulations.
*/
TEST(XMLReader_3D, test_case_1) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_1.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();
  std::vector<CuboidArgument<dim>>
      cuboidArguments{CuboidArgument<dim>{{0, 0, 0}, {40, 8, 1}, {0, 0, 0}, 1.1225, 1.0, 0.1, true, 1, 5}};
  std::vector<SphereArgument<dim>>
      sphereArguments{SphereArgument<dim>{{15.0, 15.0, 0}, 3, {0, -10, 0}, 1.1225, 1.0, 0.1, true, 1, 5}};
  std::vector<std::string> files{};
  double endTime = 5;
  double deltaT = 0.0002;
  std::string physics{"lennard"};
  std::string output{"MD"};
  auto iteration = 60;
  std::string writer{"vtk"};
  std::string algorithm{"DirectSum"};
  XMLArgument<dim> expected
      {files, endTime, deltaT, output, writer, iteration, physics, cuboidArguments, sphereArguments, algorithm,
       std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt};

  // Compare both XMLArgument
  EXPECT_EQ(*arg, expected);
}

/**
* Test that all fields of the XMLArgument are set correctly for test_case_1.xml for 2d simulations.
*/
TEST(XMLReader_2D, test_case_1) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_1.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();
  std::vector<CuboidArgument<dim>>
      cuboidArguments{CuboidArgument<dim>{{0, 0}, {40, 8}, {0, 0}, 1.1225, 1.0, 0.1, true, 1, 5}};
  std::vector<SphereArgument<dim>>
      sphereArguments{SphereArgument<dim>{{15.0, 15.0}, 3, {0, -10}, 1.1225, 1.0, 0.1, true, 1, 5}};
  std::vector<std::string> files{};
  double endTime = 5;
  double deltaT = 0.0002;
  std::string physics{"lennard"};
  std::string output{"MD"};
  auto iteration = 60;
  std::string writer{"vtk"};
  std::string algorithm{"DirectSum"};
  XMLArgument<dim> expected
      {files, endTime, deltaT, output, writer, iteration, physics, cuboidArguments, sphereArguments, algorithm,
       std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt};

  // Compare both XMLArgument
  EXPECT_EQ(*arg, expected);
}

/**
* Check that strategy selection works as expected in 3d.
*/
TEST(XMLReader_3D, test_case_2) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_2.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();

  std::string strategy{"LinkedCell"};
  double cutoffRadius = 20.0;
  std::array<int, dim> domain{20, 20, 20};
  std::array<int, dim> cellSize{1, 1, 1};
  std::vector<BoundaryType> boundary
      {BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Reflecting, BoundaryType::Reflecting,
       BoundaryType::Outflow, BoundaryType::Outflow};

  // Compare both XMLArgument
  EXPECT_EQ((*arg).getStrategy(), strategy);
  EXPECT_EQ((*arg).getCutoffRadius().value(), cutoffRadius);
  EXPECT_EQ((*arg).getDomain().value(), domain);
  EXPECT_EQ((*arg).getCellSize().value(), cellSize);
  EXPECT_EQ((*arg).getBoundaries().value(), boundary);
}

/**
* Check that strategy selection works as expected in 2d.
*/
TEST(XMLReader_2D, test_case_2) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_2.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();

  std::string strategy{"LinkedCell"};
  double cutoffRadius = 20.0;
  std::array<int, dim> domain{20, 20};
  std::array<int, dim> cellSize{1, 1};
  std::vector<BoundaryType>
      boundary{BoundaryType::Outflow, BoundaryType::Outflow, BoundaryType::Reflecting, BoundaryType::Reflecting};

  // Compare both XMLArgument
  EXPECT_EQ((*arg).getStrategy(), strategy);
  EXPECT_EQ((*arg).getCutoffRadius().value(), cutoffRadius);
  EXPECT_EQ((*arg).getDomain().value(), domain);
  EXPECT_EQ((*arg).getCellSize().value(), cellSize);
  EXPECT_EQ((*arg).getBoundaries().value(), boundary);
}

/**
* Test that strategy is direct sum in 3d.
*/
TEST(XMLReader_3D, test_case_3) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_3.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();
  std::string strategy{"DirectSum"};

  // Compare both XMLArgument
  EXPECT_EQ((*arg).getStrategy(), strategy);
}

/**
* Test that strategy is direct sum in 2d.
*/
TEST(XMLReader_2D, test_case_3) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_3.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();
  std::string strategy{"DirectSum"};

  // Compare both XMLArgument
  EXPECT_EQ((*arg).getStrategy(), strategy);
}

/**
* Test that exception is thrown for missing output attribute in test_case_3.xml.
*/
TEST(XMLReader, test_case_missing_output) { // NOLINT(cert-err58-cpp)
  // Missing attributes
  EXPECT_THROW(XMLReader<2> reader("../../tests/XMLReader/input/test_case_output.xml"), std::invalid_argument);
  EXPECT_THROW(XMLReader<3> reader("../../tests/XMLReader/input/test_case_output.xml"), std::invalid_argument);
}

/**
* Test that exception is thrown for missing physics attribute in test_case_3.xml.
*/
TEST(XMLReader, test_case_missing_physics) { // NOLINT(cert-err58-cpp)
  // Missing attributes
  EXPECT_THROW(XMLReader<2> reader("../../tests/XMLReader/input/test_case_physics.xml"), std::invalid_argument);
  EXPECT_THROW(XMLReader<3> reader("../../tests/XMLReader/input/test_case_physics.xml"), std::invalid_argument);
}

/**
* Test that exception is thrown for missing writer attribute in test_case_3.xml.
*/
TEST(XMLReader, test_case_missing_writer) { // NOLINT(cert-err58-cpp)
  // Missing attributes
  EXPECT_THROW(XMLReader<2> reader("../../tests/XMLReader/input/test_case_writer.xml"), std::invalid_argument);
  EXPECT_THROW(XMLReader<3> reader("../../tests/XMLReader/input/test_case_writer.xml"), std::invalid_argument);
}

/**
* Test that exception is thrown for missing deltaT attribute in test_case_3.xml.
*/
TEST(XMLReader, test_case_missing_delta) { // NOLINT(cert-err58-cpp)
  // Missing attributes
  EXPECT_THROW(XMLReader<2> reader("../../tests/XMLReader/input/test_case_delta.xml"), std::invalid_argument);
  EXPECT_THROW(XMLReader<3> reader("../../tests/XMLReader/input/test_case_delta.xml"), std::invalid_argument);
}

/**
* Test that exception is thrown for missing iteration attribute in test_case_3.xml.
*/
TEST(XMLReader, test_case_missing_iteration) { // NOLINT(cert-err58-cpp)
  // Missing attributes
  EXPECT_THROW(XMLReader<2> reader("../../tests/XMLReader/input/test_case_iteration.xml"), std::invalid_argument);
  EXPECT_THROW(XMLReader<3> reader("../../tests/XMLReader/input/test_case_iteration.xml"), std::invalid_argument);
}

/**
* Test that exception is thrown for missing endTime attribute in test_case_3.xml.
*/
TEST(XMLReader, test_case_missing_endtime) { // NOLINT(cert-err58-cpp)
  // Missing attributes
  EXPECT_THROW(XMLReader<2> reader("../../tests/XMLReader/input/test_case_endtime.xml"), std::invalid_argument);
  EXPECT_THROW(XMLReader<3> reader("../../tests/XMLReader/input/test_case_endtime.xml"), std::invalid_argument);
}

/**
* Test that additional files are loaded in 3d.
*/
TEST(XMLReader_3D, test_case_4) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_4.xml");

  // Create argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();

  std::vector<std::string> files{"../../tests/XMLReader/input/test_case_4.txt"};

  // Compare both XMLArgument
  EXPECT_EQ((*arg).getFiles(), files);
}

/**
* Test that additional files are loaded in 2d.
*/
TEST(XMLReader_2D, test_case_4) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_4.xml");

  // Create argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();

  std::vector<std::string> files{"../../tests/XMLReader/input/test_case_4.txt"};

  // Compare both XMLArgument
  EXPECT_EQ((*arg).getFiles(), files);
}
