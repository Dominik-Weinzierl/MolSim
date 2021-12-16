#pragma once

#include "container/ParticleContainer.h"
#include "outputWriter/VTKWriter/template/vtk-unstructured.h"

template<size_t dim>
class VTKReader {

 public:

  static void readFromFile(ParticleContainer<dim> &particleContainer, std::string &path){
    std::unique_ptr<VTKFile_t> vtkFile = VTKFile(path, xml_schema::flags::dont_validate);
    vtkFile->UnstructuredGrid()->Piece().PointData().DataArray();

    int numberOfPoints = static_cast<int>(vtkFile->UnstructuredGrid()->Piece().NumberOfPoints());
    PointData::DataArray_iterator dataIterator;

    for(auto i = 0; i < numberOfPoints; i++) {
      dataIterator = vtkFile->UnstructuredGrid()->Piece().PointData().DataArray().begin();

      double m = dataIterator->back();
      dataIterator->pop_back();
      dataIterator++;
      double v2 = dataIterator->back();;
      dataIterator->pop_back();
      double v1 = dataIterator->back();
      dataIterator->pop_back();
      double v0 = dataIterator->back();
      dataIterator->pop_back();
      dataIterator++;
      double f2 = dataIterator->back();
      dataIterator->pop_back();
      double f1 = dataIterator->back();
      dataIterator->pop_back();
      double f0 = dataIterator->back();
      dataIterator->pop_back();
      dataIterator++;
      double type = dataIterator->back();
      dataIterator->pop_back();
      dataIterator++;
      double x2 = dataIterator->back();
      dataIterator->pop_back();
      double x1 = dataIterator->back();
      dataIterator->pop_back();
      double x0 = dataIterator->back();
      dataIterator->pop_back();

      particleContainer.addParticle({{x0,x1,x2}, {v0,v1,v2}, {f0,f1,f2}, {0,0,0}, m, type});
    }
  }
};
