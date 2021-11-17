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
TEST(XMLReader, test_case_1) { // NOLINT(cert-err58-cpp)
  // Read input file
  XMLReader<3> reader("../../tests/XMLReader/input/test_case_1.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<3>> arg = reader.readXML();
  std::vector<CuboidArgument<3>> cuboidArguments{CuboidArgument<3>{{0, 0, 0}, {40, 8, 1}, {0, 0, 0}, 1.1225, 1.0, 0.1},
                                                 CuboidArgument<3>{{15.0, 15.0, 0}, {8, 8, 1}, {0, -10, 0}, 1.1225, 1.0,
                                                                   0.1}};
  std::vector<SphereArgument<3>> sphereArguments{};
  std::vector<std::string> files{};
  double endTime = 5;
  double deltaT = 0.0002;
  std::string physics{"lennard"};
  std::string output{"MD"};
  auto iteration = 60;
  std::string writer{"vtk"};
  XMLArgument<3> expected{cuboidArguments, sphereArguments, files, endTime, deltaT, output, writer, iteration, physics};

  // Compare both XMLArgument
  EXPECT_EQ(*arg, expected);
}

/**
* Test that all fields of the XMLArgument are set correctly for test_case_2.xml.
*/
TEST(XMLReader, test_case_2) { // NOLINT(cert-err58-cpp)
  // Read input file
  XMLReader<3> reader("../../tests/XMLReader/input/test_case_2.xml");

  // Create expected argument
  std::unique_ptr<XMLArgument<3>> arg = reader.readXML();
  std::vector<CuboidArgument<3>> cuboidArguments{CuboidArgument<3>{{0, 0, 0}, {5, 20, 5}, {0, 0, 0}, 1.1225, 1.0, 0.0}};
  std::vector<SphereArgument<3>> sphereArguments{SphereArgument<3>{{25, 10, 0}, 10, {-15, 0, 0}, 1.1225, 1.0, 0.0}};
  std::vector<std::string> files{};
  double endTime = 3;
  double deltaT = 0.0002;
  std::string physics{"lennard"};
  std::string output{"MD"};
  auto iteration = 60;
  std::string writer{"vtk"};
  XMLArgument<3> expected{cuboidArguments, sphereArguments, files, endTime, deltaT, output, writer, iteration, physics};

  // Compare both XMLArgument
  EXPECT_EQ(*arg, expected);
}

/**
* Test that exception is thrown for missing value in test_case_3.xml.
*/
TEST(XMLReader, test_case_3) { // NOLINT(cert-err58-cpp)
  // Missing attribute output, which is required.f
  EXPECT_THROW(XMLReader<3> reader("../../tests/XMLReader/input/test_case_3.xml"), std::invalid_argument);
}
