#include "XMLArgument.h"

XMLArgument::XMLArgument(std::vector<CuboidArgument> pCuboidArgumentsIn, std::vector<SphereArgument> pSphereArguments,
                         std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
                         std::string pWriter, int pIteration, std::string pPhysics) : Argument(std::move(pFiles),
                                                                                               pEndTime, pDeltaT,
                                                                                               std::move(pOutput),
                                                                                               std::move(pWriter),
                                                                                               pIteration,
                                                                                               std::move(pPhysics)),
                                                                                      cuboidArguments{std::move(
                                                                                          pCuboidArgumentsIn)},
                                                                                      sphereArguments{
                                                                                          std::move(pSphereArguments)} {

}
std::vector<CuboidArgument> XMLArgument::getCuboidArguments() {
  return cuboidArguments;
}

std::vector<SphereArgument> XMLArgument::getSphereArguments() {
  return sphereArguments;
}