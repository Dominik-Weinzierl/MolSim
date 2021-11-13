#pragma once

#include <generator/GeneratorArguments/CuboidArgument.h>
#include <arguments/argument/Argument.h>

class XMLArgument : public Argument {
 private:
  std::vector<CuboidArgument> cuboidArguments;

 public:
  XMLArgument(std::vector<CuboidArgument> cuboidArguments, std::vector<std::string> filesIn, double end_timeIn,
              double delta_tIn, std::string outputIn, std::string writerIn, int iterationIn, std::string physicsIn);

  std::vector<CuboidArgument> getCuboidArguments();
};
