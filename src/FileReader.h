#pragma once

#include "particles/Particle.h"

#include <list>

class FileReader {

public:
  FileReader();
  virtual ~FileReader();

  static void readFile(std::list<Particle> &particles, char *filename);
};
