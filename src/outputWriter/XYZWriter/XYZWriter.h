#pragma once

#include "particles/ParticleContainer.h"
#include "outputWriter/OutputWriter.h"

#include <fstream>
#include <list>
#include <sstream>

/**
 * XYZWriter writes files based on the XYZ file format.
 */
class XYZWriter : public OutputWriter {
 public:

  /**
   * Constructs a XYZWriter to create files based on the XYZ file format.
   * @param fileNameIn
   * @param pathIn
   * @param containerIn ParticleContainer with a Vector that contains all particles.
   */
  explicit XYZWriter(const std::string &fileNameIn, const std::string &pathIn, ParticleContainer &containerIn);

  /**
   * Writes the information about the given iteration into the file.
   * @param iteration
   */
  void writeFile(int iteration) override;

 private:

  /**
   * Iterates over all Particles and writes their current position into the file.
   */
  void plotParticles();

  std::ofstream file;
  std::stringstream strStream;
};
