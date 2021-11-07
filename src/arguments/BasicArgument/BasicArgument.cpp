#include "BasicArgument.h"

#include <utility>

BasicArgument::BasicArgument(std::string inputFileName, double end_time, double delta_t, std::string output,
                             std::string writer, int iteration, std::string physics) : Argument(
    std::move(inputFileName), end_time, delta_t, std::move(output), std::move(writer), iteration, std::move(physics)) {

}