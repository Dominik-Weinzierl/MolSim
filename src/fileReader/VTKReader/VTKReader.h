#pragma once

#include "container/ParticleContainer.h"
#include "outputWriter/VTKWriter/template/vtk-unstructured.h"

template<size_t dim>
class VTKReader {

 public:

  static void readFromFile(ParticleContainer<dim> &particleContainer, std::string &path);
};
