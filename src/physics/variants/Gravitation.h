#pragma once
#include "logger/Logger.h"
#include "physics/Physics.h"

/**
 * The Gravitation class is a subclass of Physics and therefore implements the calculation methods
 * for the active force of all particles in the particleContainer.
 * @tparam dim dimension of our simulation.
 */
class Gravitation : public PhysicsType {
};