#pragma once

#include "particles/ParticleContainer.h"
#include "outputWriter/OutputWriter.h"

#include <fstream>
#include <list>
#include <sstream>

//! XYZWriter writes files based on the XYZ file format
class XYZWriter : public OutputWriter {
 public:
  explicit XYZWriter(const std::string &file_name, const std::string &path, ParticleContainer &container);
  void writeFile(int iteration) override;

 private:
  void plotParticles();
  std::ofstream file;
  std::stringstream strStream;
};
