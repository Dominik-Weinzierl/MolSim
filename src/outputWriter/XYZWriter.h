/*
 * XYZWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "particles/ParticleContainer.h"

#include <fstream>
#include <list>

namespace outputWriter {

class XYZWriter {

public:
  XYZWriter();

  virtual ~XYZWriter();

  static void plotParticles(const ParticleContainer& particleContainer, const std::string &filename, int iteration);
};

} // namespace outputWriter
