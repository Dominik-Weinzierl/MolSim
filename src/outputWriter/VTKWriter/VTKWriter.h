#pragma once

#include "particles/Particle.h"
#include "outputWriter/VTKWriter/template/vtk-unstructured.h"
#include "outputWriter/OutputWriter.h"

#include <list>

/**
 * VTKWriter writes files based on the VTK file format.
 */
class VTKWriter : public OutputWriter {

 public:

  /**
   * Constructs a VTKWriter to create files based on the VTK file format.
   * @param pFileName
   * @param pPath
   * @param pContainer ParticleContainer with a Vector that contains all particles.
   */
  explicit VTKWriter(std::string pFileName, std::string pPath, ParticleContainer &pContainer);

  /**
   * Writes the information about the given iteration into the file.
   * @param iteration
   */
  void writeFile(int iteration) override;
 private:

  /**
   * Initializes the VTK format.
   * @param numParticles
   */
  void initializeOutput(int numParticles);

  /**
   * Writes the current velocity, position, type, oldForce and mass of the given Particle into the vtkFile.
   * @param p
   */
  void plotParticle(const Particle &p);
 private:
  std::unique_ptr<VTKFile_t> vtkFile;
};
