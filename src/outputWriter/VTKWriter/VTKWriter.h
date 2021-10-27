#pragma once

#include "particles/Particle.h"
#include "vtk-unstructured.h"
#include "outputWriter/OutputWriter.h"

#include <list>

/**
 * This class implements the functionality to generate vtk output from
 * particles.
 */
class VTKWriter : public OutputWriter {

 public:
  explicit VTKWriter(const std::string &file_name, const ParticleContainer &container);
  ~VTKWriter() override;
  void writeFile(int iteration) override;
 private:
  void initializeOutput(int numParticles);
  void plotParticle(Particle &p);
 private:
  VTKFile_t *vtkFile{};
};
