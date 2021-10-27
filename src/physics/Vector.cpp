#include "Vector.h"

Vector::Vector(double x, double y, double z) : vector{x,y,z} {};
Vector::Vector(std::array<double, 3> &vector) : vector{vector} {};

Vector Vector::operator+(Vector& other){
  vector[0] += other[0];
  vector[1] += other[1];
  vector[2] += other[2];

  return *this;
};

double Vector::operator[](int i){
  return vector[i];
};

std::ostream &Vector::operator<<(std::ostream &os) const {
  os << toString();
  return os;
};

const std::array<double, 3> &Vector::getVector() const{
  return vector;
};

void Vector::setX(double x){
  vector[0] = x;
};

void Vector::setY(double y){
  vector[1] = y;
};

void Vector::setZ(double z){
  vector[2] = z;
}

std::string Vector::toString() const{
  return "x: " + std::to_string(vector[0]) + " y: " + std::to_string(vector[1]) + " z: " + std::to_string(vector[2]);
}