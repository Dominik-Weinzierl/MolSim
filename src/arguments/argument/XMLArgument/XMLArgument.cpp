#include "XMLArgument.h"

XMLArgument::XMLArgument(std::vector<CuboidArgument> cuboidArgumentsIn,
                         std::vector<std::string> filesIn,
                         double end_timeIn,
                         double delta_tIn,
                         std::string outputIn,
                         std::string writerIn,
                         int iterationIn,
                         std::string physicsIn)
    : Argument(std::move(filesIn), end_timeIn, delta_tIn, std::move(outputIn), std::move(writerIn), iterationIn,
               std::move(physicsIn)), cuboidArguments{std::move(cuboidArgumentsIn)} {

}
std::vector<CuboidArgument> XMLArgument::getCuboidArguments() {
  return cuboidArguments;
}
