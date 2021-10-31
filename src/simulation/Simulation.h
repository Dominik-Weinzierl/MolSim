#pragma once

#include "outputWriter/VTKWriter/VTKWriter.h"
#include <iostream>
#include <physics/gravitation/Gravitation.h>
#include <arguments/Argument/Argument.h>
#include <arguments/BasicArgumentParser/BasicArgumentParser.h>

class Simulation {
 protected:
  static constexpr double start_time = 0;
  static void performSimulation(OutputWriter &writer, const Physics &physics, ParticleContainer &particleContainer,
                                Argument &arg);
};
