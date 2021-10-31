#pragma once

#include "particles/ParticleContainer.h"
#include "outputWriter/OutputWriter.h"

#include <fstream>
#include <list>
#include <sstream>

class XYZWriter : public OutputWriter {
 public:
  explicit XYZWriter(const std::string &file_name, const std::string &path, ParticleContainer &container);
  ~XYZWriter() override = default;
  void writeFile(int iteration) override;

 private:
  void plotParticles(int iteration);
  std::ofstream file;
  std::stringstream strStream;
};
