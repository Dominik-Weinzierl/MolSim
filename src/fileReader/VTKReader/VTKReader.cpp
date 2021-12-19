#include "VTKReader.h"

template<>
void VTKReader<2>::readFromFile(ParticleContainer<2> &particleContainer, std::string &path) {
  std::unique_ptr<VTKFile_t> vtkFile = VTKFile(path, xml_schema::flags::dont_validate);
  vtkFile->UnstructuredGrid()->Piece().PointData().DataArray();

  int numberOfPoints = static_cast<int>(vtkFile->UnstructuredGrid()->Piece().NumberOfPoints());
  PointData::DataArray_iterator dataIterator;

  for(auto i = 0; i < numberOfPoints; i++) {
    dataIterator = vtkFile->UnstructuredGrid()->Piece().PointData().DataArray().begin();

    double m = dataIterator->back();
    dataIterator->pop_back();
    dataIterator++;
    dataIterator->pop_back();
    double v1 = dataIterator->back();
    dataIterator->pop_back();
    double v0 = dataIterator->back();
    dataIterator->pop_back();
    dataIterator++;
    dataIterator->pop_back();
    double f1 = dataIterator->back();
    dataIterator->pop_back();
    double f0 = dataIterator->back();
    dataIterator->pop_back();
    dataIterator++;
    int type = static_cast<int>(dataIterator->back());
    dataIterator->pop_back();
    dataIterator++;
    double zeroCrossing = dataIterator->back();
    dataIterator->pop_back();
    dataIterator++;
    double potentialWellDepth = dataIterator->back();
    dataIterator->pop_back();
    dataIterator++;
    dataIterator->pop_back();
    double x1 = dataIterator->back();
    dataIterator->pop_back();
    double x0 = dataIterator->back();
    dataIterator->pop_back();

    Particle<2> p{{x0,x1}, {v0,v1}, {f0,f1}, {0,0}, m, zeroCrossing, potentialWellDepth, type};
    particleContainer.addParticle(p);
  }
}

template<>
void VTKReader<3>::readFromFile(ParticleContainer<3> &particleContainer, std::string &path){
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
  int type = static_cast<int>(dataIterator->back());
  dataIterator->pop_back();
  dataIterator++;
  double zeroCrossing = dataIterator->back();
  dataIterator->pop_back();
  dataIterator++;
  double potentialWellDepth = dataIterator->back();
  dataIterator->pop_back();
  dataIterator++;
  double x2 = dataIterator->back();
  dataIterator->pop_back();
  double x1 = dataIterator->back();
  dataIterator->pop_back();
  double x0 = dataIterator->back();
  dataIterator->pop_back();

  particleContainer.addParticle({{x0,x1,x2}, {v0,v1,v2}, {f0,f1,f2}, {0,0,0}, m, zeroCrossing, potentialWellDepth, type});
  }
}
