#pragma once

#include <list>
#include <particles/ParticleContainer.h>

class FileReader {

 public:
  FileReader();
  virtual ~FileReader();

  static void readFile(ParticleContainer &particleContainer, const std::string &filename);
};
