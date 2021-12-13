#pragma once

#include "container/ParticleContainer.h"
#include "outputWriter/OutputWriter.h"

/**
 * DummyWriter writes no files.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class DummyWriter : public OutputWriter<dim> {
 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * Constructs a XYZWriter to create files based on the XYZ file format.
   * @param pFileName output filename
   * @param pPath output path
   * @param pContainer ParticleContainer with a Vector that contains all Particle(s).
   */
  explicit DummyWriter(std::string pFileName, ParticleContainer<dim> &pContainer) : OutputWriter<dim>(
      std::move(pFileName), pContainer) {};

  //----------------------------------------Methods----------------------------------------

  /**
  * Writes no information.
  * @param iteration current iteration of the simulation
  */
  void writeFile([[maybe_unused]] int iteration) override {};
};
