#include <string>
#include "particles/ParticleContainer.h"
#include "particles/Particle.h"

#pragma once

class OutputWriter {
 public:
  OutputWriter(std::string fileName, const ParticleContainer &container);
  virtual ~OutputWriter() = default;

  virtual void writeFile(int iteration) = 0;
 protected:
  const std::string fileName;
  const ParticleContainer &container;
};

