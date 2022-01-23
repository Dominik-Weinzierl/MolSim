#include "gtest/gtest.h"
#include "outputWriter/ProfileWriter/ProfileWriter.h"
#include "container/DirectSum/DirectSumContainer.h"
#include "fstream"

/**
* Test correct calculation of average velocity.
*/
TEST(ProfileWriter2D, avgV) {
  constexpr size_t dim = 2;
  DirectSumContainer<dim> c;
  c.addParticle({{0, 0}, {1, 0}, 0});
  c.addParticle({{0, 2}, {2, 0}, 0});
  std::string path{"../../tests/outputWriter"};
  ProfileWriter<dim> w{1, 100, true, false, {2, 2}, path};
  w.generateProfiles(c, 0);
  std::ifstream file;
  file.open("../../tests/outputWriter/velprofile.csv", std::ios::in);
  std::string line;
  std::getline(file, line);
  EXPECT_EQ(line, "iteration,0");
  std::getline(file, line);
  EXPECT_EQ(line, "0,1.50000");
}

/**
* Test correct calculation of bins.
*/
TEST(ProfileWriter2D, correctBins) {
  constexpr size_t dim = 2;
  DirectSumContainer<dim> c;
  c.addParticle({{0, 0}, {1, 0}, 0});
  c.addParticle({{2, 2}, {2, 0}, 0});
  std::string path{"../../tests/outputWriter"};
  ProfileWriter<dim> w{2, 100, true, false, {4, 4}, path};
  w.generateProfiles(c, 0);
  std::ifstream file;
  file.open("../../tests/outputWriter/velprofile.csv", std::ios::in);
  std::string line;
  std::getline(file, line);
  EXPECT_EQ(line, "iteration,0,1");
  std::getline(file, line);
  EXPECT_EQ(line, "0,1.00000,2.00000");
}


/**
* Test correct calculation of average velocity.
*/
TEST(ProfileWriter3D, avgV) {
  constexpr size_t dim = 3;
  DirectSumContainer<dim> c;
  c.addParticle({{0, 0, 0}, {1, 0, 0}, 0});
  c.addParticle({{0, 2, 0}, {2, 0, 0}, 0});
  std::string path{"../../tests/outputWriter"};
  ProfileWriter<dim> w{1, 100, true, false, {2, 2, 2}, path};
  w.generateProfiles(c, 0);
  std::ifstream file;
  file.open("../../tests/outputWriter/velprofile.csv", std::ios::in);
  std::string line;
  std::getline(file, line);
  EXPECT_EQ(line, "iteration,0");
  std::getline(file, line);
  EXPECT_EQ(line, "0,1.50000");
}

/**
* Test correct calculation of bins.
*/
TEST(ProfileWriter3D, correctBins) {
  constexpr size_t dim = 3;
  DirectSumContainer<dim> c;
  c.addParticle({{0, 0, 0}, {1, 0, 0}, 0});
  c.addParticle({{2, 2, 0}, {2, 0, 0}, 0});
  std::string path{"../../tests/outputWriter"};
  ProfileWriter<dim> w{2, 100, true, false, {4, 4, 4}, path};
  w.generateProfiles(c, 0);
  std::ifstream file;
  file.open("../../tests/outputWriter/velprofile.csv", std::ios::in);
  std::string line;
  std::getline(file, line);
  EXPECT_EQ(line, "iteration,0,1");
  std::getline(file, line);
  EXPECT_EQ(line, "0,1.00000,2.00000");
}

/**
* Test correct calculation of density.
*/
TEST(ProfileWriter3D, density) {
  constexpr size_t dim = 3;
  DirectSumContainer<dim> c;
  c.addParticle({{0, 0, 0}, {1, 0, 0}, 0});
  c.addParticle({{0, 2, 0}, {2, 0, 0}, 0});
  std::string path{"../../tests/outputWriter"};
  ProfileWriter<dim> w{1, 100, false, true, {2, 2, 2}, path};
  w.generateProfiles(c, 0);
  std::ifstream file;
  file.open("../../tests/outputWriter/densprofile.csv", std::ios::in);
  std::string line;
  std::getline(file, line);
  EXPECT_EQ(line, "iteration,0");
  std::getline(file, line);
  EXPECT_EQ(line, "0,0.250000");
}

/**
* Test correct calculation of density.
*/
TEST(ProfileWriter2D, density) {
  constexpr size_t dim = 2;
  DirectSumContainer<dim> c;
  c.addParticle({{0, 0}, {1, 0}, 0});
  c.addParticle({{0, 2}, {2, 0}, 0});
  std::string path{"../../tests/outputWriter"};
  ProfileWriter<dim> w{1, 100, false, true, {2, 2}, path};
  w.generateProfiles(c, 0);
  std::ifstream file;
  file.open("../../tests/outputWriter/densprofile.csv", std::ios::in);
  std::string line;
  std::getline(file, line);
  EXPECT_EQ(line, "iteration,0");
  std::getline(file, line);
  EXPECT_EQ(line, "0,0.500000");
}