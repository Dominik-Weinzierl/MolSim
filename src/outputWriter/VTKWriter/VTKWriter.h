#pragma once

#include "particles/Particle.h"
#include "outputWriter/VTKWriter/template/vtk-unstructured.h"
#include "outputWriter/OutputWriter.h"

#include <list>
#include <fstream>

/**
 * VTKWriter writes files based on the VTK file format.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class VTKWriter : public OutputWriter<dim> {
  /**
   * VTKFile in a reusable way.
   */
  std::unique_ptr<VTKFile_t> vtkFile;

  /**
   * Writes the current velocity, position, type, oldForce and mass of the given Particle into the vtkFile.
   * @param p Particle
   */
  void plotParticle(const Particle<dim> &p);
  // Since we expect only dim two or three, there is no default implementation required.

 public:

  /**
   * Constructs a VTKWriter to create files based on the VTK file format.
   * @param pFileName output filename
   * @param pPath output path
   * @param pContainer ParticleContainer with a Vector that contains all Particle(s).
   */
  explicit VTKWriter(std::string pFileName, std::string pPath, ParticleContainer<dim> &pContainer) : OutputWriter<dim>(
      std::move(pFileName), std::move(pPath), pContainer) {}

  /**
   * Writes the information about the given iteration into the file.
   * @param iteration current iteration of the simulation
   */
  void writeFile(int iteration) override {
    std::stringstream strStream;
    strStream << this->path << "/" << this->fileName << "_" << std::setfill('0') << std::setw(4) << iteration << ".vtu";
    std::ofstream file(strStream.str().c_str());

    // Filter particle container
    std::vector<Particle<dim>> filtered;
    std::copy_if(this->container.begin(), this->container.end(), std::back_inserter(filtered), [](auto &p) {
      return p.getType() != -1;
    });

    initializeOutput(static_cast<int>(filtered.size()));
    for (const auto &particle: filtered) {
      plotParticle(particle);
    }

    VTKFile(file, *vtkFile);
  }
 private:

  /**
   * Initializes the VTK format.
   * @param numParticles amount of Particle(s) used in our simulation
   */
  void initializeOutput(int numParticles) {
    vtkFile = std::make_unique<VTKFile_t>("UnstructuredGrid");

    // per point, we add type, position, velocity and force
    PointData pointData;
    DataArray_t mass(type::Float32, "mass", 1);
    DataArray_t velocity(type::Float32, "velocity", 3);
    DataArray_t forces(type::Float32, "force", 3);
    DataArray_t type(type::Int32, "type", 1);
    pointData.DataArray().push_back(mass);
    pointData.DataArray().push_back(velocity);
    pointData.DataArray().push_back(forces);
    pointData.DataArray().push_back(type);

    CellData cellData; // we don't have cell data => leave it empty

    // 3 coordinates
    Points points;
    DataArray_t pointCoordinates(type::Float32, "points", 3);
    points.DataArray().push_back(pointCoordinates);

    Cells cells; // we don't have cells, => leave it empty
    // for some reasons, we have to add a dummy entry for paraview
    DataArray_t cells_data(type::Float32, "types", 0);
    cells.DataArray().push_back(cells_data);

    PieceUnstructuredGrid_t piece(pointData, cellData, points, cells, numParticles, 0);
    UnstructuredGrid_t unstructuredGrid(piece);
    vtkFile->UnstructuredGrid(unstructuredGrid);
  }
};