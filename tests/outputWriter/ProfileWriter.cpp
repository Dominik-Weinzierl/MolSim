#include "gtest/gtest.h"
#include "outputWriter/ProfileWriter/ProfileWriter.h"
#include "container/DirectSum/DirectSumContainer.h"
#include "fstream"

/**
* Test correct calculation of average velocity
*/
TEST(ProfileWriter, avgV) {
  constexpr size_t dim = 2;
  DirectSumContainer<dim> c;
  c.addParticle({{0, 0}, {1, 0}, 0});
  c.addParticle({{0, 2}, {2, 0}, 0});
  std::string path{"../../tests/outputWriter/output"};
  ProfileWriter<dim> w{1, 100, true, false, path};
  w.generateProfiles(c, 0);
  std::ifstream file;
  file.open("../../tests/outputWriter/output/velprofile.csv", std::ios::in);
  std::string line;
  //todo: read line correctly - how?
  std::getline(file, line);
  EXPECT_EQ(line, "aa");
}