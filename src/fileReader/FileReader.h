#pragma once

#include "particles/ParticleContainer.h"

#include <list>

class FileReader {

 public:
  FileReader();
  virtual ~FileReader();

  static void readFile(ParticleContainer &particleContainer, const std::string &filename);
};
