#pragma once

#include <cstddef>
#include "particles/ParticleContainer.h"
#include "boundaryConditions/BoundaryCondition.h"

template<size_t dim>
class Reflection : public BoundaryCondition {};
