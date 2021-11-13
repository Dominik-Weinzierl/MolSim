#include "CuboidArgument.h"

#include <utility>

CuboidArgument::CuboidArgument(Vector<> pStartingCoordinates, std::vector<int> pDimensions, Vector<> pInitialVelocity,
                               double pDistance, double pMass, double pMeanValue) : startingCoordinates{
    pStartingCoordinates}, dimensions{std::move(pDimensions)}, initialVelocity{pInitialVelocity}, distance{pDistance},
                                                                                    mass{pMass}, meanValue{pMeanValue} {

}
