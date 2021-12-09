#include "VTKWriter.h"

template<>
void VTKWriter<3>::plotParticle(const Particle<3> &p) {
  PointData::DataArray_sequence &pointDataSequence = vtkFile->UnstructuredGrid()->Piece().PointData().DataArray();
  PointData::DataArray_iterator dataIterator = pointDataSequence.begin();

  dataIterator->push_back(p.getM());
  // cout << "Appended mass data in: " << dataIterator->Name();

  dataIterator++;
  dataIterator->push_back(p.getV()[0]);
  dataIterator->push_back(p.getV()[1]);
  dataIterator->push_back(p.getV()[2]);
  // cout << "Appended velocity data in: " << dataIterator->Name();

  dataIterator++;
  dataIterator->push_back(p.getOldF()[0]);
  dataIterator->push_back(p.getOldF()[1]);
  dataIterator->push_back(p.getOldF()[2]);
  // cout << "Appended force data in: " << dataIterator->Name();

  dataIterator++;
  dataIterator->push_back(p.getType());

  Points::DataArray_sequence &pointsSequence = vtkFile->UnstructuredGrid()->Piece().Points().DataArray();
  Points::DataArray_iterator pointsIterator = pointsSequence.begin();
  pointsIterator->push_back(p.getX()[0]);
  pointsIterator->push_back(p.getX()[1]);
  pointsIterator->push_back(p.getX()[2]);
}

template<>
void VTKWriter<2>::plotParticle(const Particle<2> &p) {
  PointData::DataArray_sequence &pointDataSequence = vtkFile->UnstructuredGrid()->Piece().PointData().DataArray();
  PointData::DataArray_iterator dataIterator = pointDataSequence.begin();

  dataIterator->push_back(p.getM());
  // cout << "Appended mass data in: " << dataIterator->Name();

  dataIterator++;
  dataIterator->push_back(p.getV()[0]);
  dataIterator->push_back(p.getV()[1]);
  dataIterator->push_back(0.0);
  // cout << "Appended velocity data in: " << dataIterator->Name();

  dataIterator++;
  dataIterator->push_back(p.getOldF()[0]);
  dataIterator->push_back(p.getOldF()[1]);
  dataIterator->push_back(0.0);
  // cout << "Appended force data in: " << dataIterator->Name();

  dataIterator++;
  dataIterator->push_back(p.getType());

  Points::DataArray_sequence &pointsSequence = vtkFile->UnstructuredGrid()->Piece().Points().DataArray();
  Points::DataArray_iterator pointsIterator = pointsSequence.begin();
  pointsIterator->push_back(p.getX()[0]);
  pointsIterator->push_back(p.getX()[1]);
  pointsIterator->push_back(0.0);
}
