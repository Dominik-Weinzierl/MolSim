#pragma once

#include <generator/GeneratorArguments/CuboidArgument.h>
#include <arguments/argument/Argument.h>

class XMLArgument : public Argument {
 private:
  std::vector<CuboidArgument> cuboidArguments;

 public:
  XMLArgument(std::vector<CuboidArgument> cuboidArguments, std::vector<std::string> files, double end_time,
              double delta_t, std::string output, std::string writer, int iteration, std::string physics);

};
