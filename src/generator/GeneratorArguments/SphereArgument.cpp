

#include "SphereArgument.h"
SphereArgument::SphereArgument(Vector<> pCenterCoordinates, int pRadius, Vector<> pInitialVelocity, double pDistance,
                               double pMass, double pMeanValue) : centerCoordinates{pCenterCoordinates},
                                                                  radius{pRadius}, initialVelocity{pInitialVelocity},
                                                                  distance{pDistance}, mass{pMass},
                                                                  meanValue{pMeanValue} {
}
