#pragma once

#include <fstream>
#include <list>
#include <sstream>

#include "container/ParticleContainer.h"
#include "outputWriter/OutputWriter.h"

/**
 * XYZWriter writes files based on the XYZ file format.
 * @tparam dim dimension of our simulation
 */
template<size_t dim>
class XYZWriter : public OutputWriter<dim> {

  /**
   * File to write to.
   */
  std::ofstream file;

  /**
   * Stream used to store the fileName in order to open the file.
   */
  std::stringstream strStream;

  //----------------------------------------Methods----------------------------------------

  /**
   * Iterates over all Particles and writes their current position into the file.
   */
  void plotParticles() {
    auto particles = XYZWriter<dim>::container.getParticles();
    for (auto &p: particles) {
      auto &x = p.getX();
      file << "Ar ";
      file.setf(std::ios_base::showpoint);
      for (auto &xi: x) {
        file << xi << " ";
      }

      file << std::endl;
    }
  }
 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * Constructs a XYZWriter to create files based on the XYZ file format.
   * @param pFileName output filename
   * @param pPath output path
   * @param pContainer ParticleContainer with a Vector that contains all Particle(s)
   */
  explicit XYZWriter(std::string pFileName, std::string pPath, ParticleContainer<dim> &pContainer) : OutputWriter<dim>(
      std::move(pFileName), std::move(pPath), pContainer) {};

  //----------------------------------------Methods----------------------------------------

  /**
   * Writes the information about the given iteration into the file.
   * @param iteration current iteration of the simulation
   */
  void writeFile(int iteration) override {
    strStream << this->path << "/" << this->fileName << "_" << std::setfill('0') << std::setw(4) << iteration << ".xyz";
    file.open(strStream.str().c_str());
    file << this->container.getParticles().size() << std::endl;
    file << "Generated by MolSim. See http://openbabel.org/wiki/XYZ_(format) for "
            "file format doku." << std::endl;
    plotParticles();
    file.close();
  }
};
