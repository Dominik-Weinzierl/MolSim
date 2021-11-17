#include <gtest/gtest.h>
#include <fileReader/XMLReader/XMLReader.h>
/**
 * ***************************************************
 * Test correct functionality of the class XMLReader
 * ******************************************+********
 */


/**
* Test that all fields of the XMLArgument are set correctly for test_case_1.xml
*/
TEST(XMLReader, test_case_1) {
  XMLReader<3> reader("../../tests/XMLReader/input/test_case_1.xml");
  std::unique_ptr<XMLArgument<3>> arg = reader.readXML();
  EXPECT_EQ(arg->getCuboidArguments().size(), 2);
  EXPECT_EQ(arg->getSphereArguments().size(), 0);
  EXPECT_EQ(arg->getDeltaT(), 0.0002);
  EXPECT_EQ(arg->getEndTime(), 5);
  EXPECT_EQ(arg->getPhysics(), "lennard");
  EXPECT_EQ(arg->getIteration(), 60);
  EXPECT_EQ(arg->getWriter(), "vtk");
  EXPECT_EQ(arg->getOutput(), "MD");
  EXPECT_EQ(arg->getFiles().size(), 0);

  CuboidArgument cub_1 = arg->getCuboidArguments()[0];
  EXPECT_DOUBLE_EQ(cub_1.distance, 1.1225);
  EXPECT_DOUBLE_EQ(cub_1.mass, 1);
  EXPECT_DOUBLE_EQ(cub_1.meanValue, 0.1);
  EXPECT_DOUBLE_EQ(cub_1.startingCoordinates[0], 0);
  EXPECT_DOUBLE_EQ(cub_1.startingCoordinates[1], 0);
  EXPECT_DOUBLE_EQ(cub_1.startingCoordinates[2], 0);
  EXPECT_DOUBLE_EQ(cub_1.initialVelocity[0], 0);
  EXPECT_DOUBLE_EQ(cub_1.initialVelocity[1], 0);
  EXPECT_DOUBLE_EQ(cub_1.initialVelocity[2], 0);
  EXPECT_EQ(cub_1.dimensions[0], 40);
  EXPECT_EQ(cub_1.dimensions[1], 8);
  EXPECT_EQ(cub_1.dimensions[2], 1);

  CuboidArgument cub_2 = arg->getCuboidArguments()[1];
  EXPECT_DOUBLE_EQ(cub_2.distance, 1.1225);
  EXPECT_DOUBLE_EQ(cub_2.mass, 1);
  EXPECT_DOUBLE_EQ(cub_2.meanValue, 0.1);
  EXPECT_DOUBLE_EQ(cub_2.startingCoordinates[0], 15.0);
  EXPECT_DOUBLE_EQ(cub_2.startingCoordinates[1], 15.0);
  EXPECT_DOUBLE_EQ(cub_2.startingCoordinates[2], 0);
  EXPECT_DOUBLE_EQ(cub_2.initialVelocity[0], 0);
  EXPECT_DOUBLE_EQ(cub_2.initialVelocity[1], -10.0);
  EXPECT_DOUBLE_EQ(cub_2.initialVelocity[2], 0);
  EXPECT_EQ(cub_2.dimensions[0], 8);
  EXPECT_EQ(cub_2.dimensions[1], 8);
  EXPECT_EQ(cub_2.dimensions[2], 1);
}


/**
* Test that all fields of the XMLArgument are set correctly for test_case_2.xml
*/
TEST(xmlReader, test_case_2) {
  XMLReader<3> reader("../../tests/XMLReader/input/test_case_2.xml");
  std::unique_ptr<XMLArgument<3>> arg = reader.readXML();
  EXPECT_EQ(arg->getCuboidArguments().size(), 1);
  EXPECT_EQ(arg->getSphereArguments().size(), 1);
  EXPECT_EQ(arg->getDeltaT(), 0.0002);
  EXPECT_EQ(arg->getEndTime(), 3);
  EXPECT_EQ(arg->getPhysics(), "lennard");
  EXPECT_EQ(arg->getIteration(), 60);
  EXPECT_EQ(arg->getWriter(), "vtk");
  EXPECT_EQ(arg->getOutput(), "MD");
  EXPECT_EQ(arg->getFiles().size(), 0);

  CuboidArgument cub = arg->getCuboidArguments()[0];
  EXPECT_DOUBLE_EQ(cub.distance, 1.1225);
  EXPECT_DOUBLE_EQ(cub.mass, 1);
  EXPECT_DOUBLE_EQ(cub.meanValue, 0);
  EXPECT_DOUBLE_EQ(cub.startingCoordinates[0], 0);
  EXPECT_DOUBLE_EQ(cub.startingCoordinates[1], 0);
  EXPECT_DOUBLE_EQ(cub.startingCoordinates[2], 0);
  EXPECT_DOUBLE_EQ(cub.initialVelocity[0], 0);
  EXPECT_DOUBLE_EQ(cub.initialVelocity[1], 0);
  EXPECT_DOUBLE_EQ(cub.initialVelocity[2], 0);
  EXPECT_EQ(cub.dimensions[0], 5);
  EXPECT_EQ(cub.dimensions[1], 20);
  EXPECT_EQ(cub.dimensions[2], 5);

  SphereArgument sph = arg->getSphereArguments()[0];
  EXPECT_DOUBLE_EQ(sph.distance, 1.1225);
  EXPECT_DOUBLE_EQ(sph.mass, 3);
  EXPECT_DOUBLE_EQ(sph.meanValue, 0);
  EXPECT_DOUBLE_EQ(sph.centerCoordinates[0], 25);
  EXPECT_DOUBLE_EQ(sph.centerCoordinates[1], 10);
  EXPECT_DOUBLE_EQ(sph.centerCoordinates[2], 0);
  EXPECT_DOUBLE_EQ(sph.initialVelocity[0], -15);
  EXPECT_DOUBLE_EQ(sph.initialVelocity[1], 0);
  EXPECT_DOUBLE_EQ(sph.initialVelocity[2], 0);
  EXPECT_EQ(sph.radius, 10);
}