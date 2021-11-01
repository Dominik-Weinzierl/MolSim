#pragma once

#include <list>
#include <particles/ParticleContainer.h>

//! FileReader class reads a file line and prints the read line to the terminal
//! ReadFile Method adds the particles to the given particleContainer
class FileReader {
 public:
  static void readFile(ParticleContainer &particleContainer, const std::string &filename);
};
