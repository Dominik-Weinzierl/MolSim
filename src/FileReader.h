/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "particles/Particle.h"

#include <list>

class FileReader {

public:
  FileReader();
  virtual ~FileReader();

  static void readFile(std::list<Particle> &particles, char *filename);
};
