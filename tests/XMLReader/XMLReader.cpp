#include <gtest/gtest.h>
#include <fileReader/XMLReader/XMLReader.h>
/**
 * ***************************************************
 * Test correct functionality of the class XMLReader.
 * ******************************************+********
 */


/**
* Test that all fields of the XMLArgument are set correctly for test_case_1.xml.
*/
TEST(XMLReader_3D, test_case_1) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_1.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();
  std::vector<CuboidArgument<dim>> cuboidArguments
      {CuboidArgument<dim>{{0, 0, 0}, {40, 8, 1}, {0, 0, 0}, 1.1225, 1.0, 0.1},
       CuboidArgument<dim>{{15.0, 15.0, 0}, {8, 8, 1}, {0, -10, 0}, 1.1225, 1.0, 0.1}};
  std::vector<SphereArgument<dim>> sphereArguments{};
  std::vector<std::string> files{};
  double endTime = 5;
  double deltaT = 0.0002;
  std::string physics{"lennard"};
  std::string output{"MD"};
  auto iteration = 60;
  std::string writer{"vtk"};
  XMLArgument<dim>
      expected{cuboidArguments, sphereArguments, files, endTime, deltaT, output, writer, iteration, physics};

  // Compare both XMLArgument
  EXPECT_EQ(*arg, expected);
}

/**
* Test that all fields of the XMLArgument are set correctly for test_case_2.xml.
*/
TEST(XMLReader_3D, test_case_2) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_2.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();
  std::vector<CuboidArgument<dim>>
      cuboidArguments{CuboidArgument<dim>{{0, 0, 0}, {5, 20, 5}, {0, 0, 0}, 1.1225, 1.0, 0.0}};
  std::vector<SphereArgument<dim>> sphereArguments{SphereArgument<dim>{{25, 10, 0}, 10, {-15, 0, 0}, 1.1225, 1.0, 0.0}};
  std::vector<std::string> files{};
  double endTime = 3;
  double deltaT = 0.0002;
  std::string physics{"lennard"};
  std::string output{"MD"};
  auto iteration = 60;
  std::string writer{"vtk"};
  XMLArgument<dim>
      expected{cuboidArguments, sphereArguments, files, endTime, deltaT, output, writer, iteration, physics};

  // Compare both XMLArgument
  EXPECT_EQ(*arg, expected);
}

/**
* Test that exception is thrown for missing value in test_case_3.xml.
*/
TEST(XMLReader_3D, test_case_3) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  // Missing attribute output, which is required.f
  EXPECT_THROW(XMLReader<dim> reader("../../tests/XMLReader/input/test_case_3.xml"), std::invalid_argument);
}

/**
* Test that all fields of the XMLArgument are set correctly for test_case_1.xml.
*/
TEST(XMLReader_2D, test_case_1) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_1.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();
  std::vector<CuboidArgument<dim>> cuboidArguments{CuboidArgument<dim>{{0, 0}, {40, 8}, {0, 0}, 1.1225, 1.0, 0.1},
                                                   CuboidArgument<dim>{{15.0, 15.0}, {8, 8}, {0, -10}, 1.1225, 1.0,
                                                                       0.1}};
  std::vector<SphereArgument<dim>> sphereArguments{};
  std::vector<std::string> files{};
  double endTime = 5;
  double deltaT = 0.0002;
  std::string physics{"lennard"};
  std::string output{"MD"};
  auto iteration = 60;
  std::string writer{"vtk"};
  XMLArgument<dim>
      expected{cuboidArguments, sphereArguments, files, endTime, deltaT, output, writer, iteration, physics};

  // Compare both XMLArgument
  EXPECT_EQ(*arg, expected);
}

/**
* Test that all fields of the XMLArgument are set correctly for test_case_2.xml.
*/
TEST(XMLReader_2D, test_case_2) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Read input file
  XMLReader<dim> reader("../../tests/XMLReader/input/test_case_2.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();
  std::vector<CuboidArgument<dim>> cuboidArguments{CuboidArgument<dim>{{0, 0}, {5, 20}, {0, 0}, 1.1225, 1.0, 0.0}};
  std::vector<SphereArgument<dim>> sphereArguments{SphereArgument<dim>{{25, 10}, 10, {-15, 0}, 1.1225, 1.0, 0.0}};
  std::vector<std::string> files{};
  double endTime = 3;
  double deltaT = 0.0002;
  std::string physics{"lennard"};
  std::string output{"MD"};
  auto iteration = 60;
  std::string writer{"vtk"};
  XMLArgument<dim>
      expected{cuboidArguments, sphereArguments, files, endTime, deltaT, output, writer, iteration, physics};

  // Compare both XMLArgument
  EXPECT_EQ(*arg, expected);
}

/**
* Test that exception is thrown for missing value in test_case_3.xml.
*/
TEST(XMLReader_2D, test_case_3) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 2;

  // Missing attribute output, which is required.f
  EXPECT_THROW(XMLReader<dim> reader("../../tests/XMLReader/input/test_case_3.xml"), std::invalid_argument);
}
