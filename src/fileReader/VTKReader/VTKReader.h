#pragma once

#include "container/ParticleContainer.h"
#include "outputWriter/VTKWriter/template/vtk-unstructured.h"

/**
 * Class to read files in VTK format.
 * @tparam dim
 */
template<size_t dim>
class VTKReader {

 public:

  /**
   * Method that reads given VTK file.
   * @param particleContainer Particle Container to add particles given through the VTk file to.
   * @param path Path to the VTK file.
   */
  static void readFromFile(ParticleContainer<dim> &particleContainer, const std::string &path);
};
