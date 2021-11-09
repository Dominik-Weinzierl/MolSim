#include "BasicArgument.h"

#include <utility>

BasicArgument::BasicArgument(std::vector<std::string> files, double end_time, double delta_t, std::string output,
                             std::string writer, int iteration, std::string physics) : Argument(std::move(files),
                                                                                                end_time, delta_t,
                                                                                                std::move(output),
                                                                                                std::move(writer),
                                                                                                iteration,
                                                                                                std::move(physics)) {

}
