#include <gtest/gtest.h>
#include <fileReader/XMLReader/XMLReader.h>
/**
 * ***************************************************
 * Test correct functionality of the class XMLReader
 * ******************************************+********
 */

/**
* Test that all fields of the XMLArgument are set correctly for input.xml
*/
TEST(xmlReader, smallSample) {
  XMLReader<3> reader("XMLReader/input.xml");
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