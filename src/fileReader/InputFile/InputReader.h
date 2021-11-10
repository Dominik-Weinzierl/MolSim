#pragma once

#include <list>
#include <particles/ParticleContainer.h>

/**
 * FileReader class reads a file line and prints the read line to the terminal.
 */
class InputReader {
 public:

  /**
   * ReadFile Method adds the particles to the given particleContainer.
   * @param particleContainer
   * @param filename
   */
  static void readFile(ParticleContainer &particleContainer, const std::string &filename);
};
