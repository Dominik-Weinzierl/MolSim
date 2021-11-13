#include "BasicArgument.h"

#include <utility>

BasicArgument::BasicArgument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
                             std::string pWriter, int pIteration, std::string pPhysics) : Argument(std::move(pFiles),
                                                                                                   pEndTime, pDeltaT,
                                                                                                   std::move(pOutput),
                                                                                                   std::move(pWriter),
                                                                                                   pIteration,
                                                                                                   std::move(
                                                                                                       pPhysics)) {

}
