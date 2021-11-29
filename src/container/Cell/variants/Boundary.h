#pragma once

#include "physics/variants/LennardJones.h"
#include "container/Cell/Cell.h"
#include "particles/Particle.h"

enum BoardDirectionType {
  TOP, LEFT, RIGHT, BOTTOM, FRONT, BACK
};

/**
 *
 * @tparam T boundary condition
 * @tparam dim dimension for the simulation
 */
template<size_t dim>
class Boundary : public Cell<dim> {

 private:
  BoardDirectionType borderDirection;

  const double sixthSqrtOfTwo = std::pow(2, 1 / 6);

 public:

  explicit Boundary(BoundaryType pBoundaryType, BoardDirectionType pBorderDirection) : borderDirection{
      pBorderDirection}, Cell<dim>(pBoundaryType) {}

  void applyCellProperties() override {}

  double getReflectionDistance(Particle<dim> &p) const {
    return sixthSqrtOfTwo * p.getZeroCrossing();
  }
};

/*//Instant Reflection
template<size_t dim>
void Boundary<Reflection, dim>::reflect2d(Particle<dim>& p) {
  auto reflectionDistance{getReflectionDistance(p)};
  auto force{p.getF()};

  //Check top & bottom
  if(borderDirection[0] && (border[1] - p.getX()[1] < reflectionDistance) ||
      borderDirection[1] && (p.getX()[1] < reflectionDistance)){
    p.setF(p.getF()[0], -p.getF()[1]);
  }

  //Check left & right
  if(borderDirection[2] && (p.getX()[0] < reflectionDistance) ||
      borderDirection[3] && (border[0] - p.getX()[0] < reflectionDistance)) {
    p.setF(-p.getF()[0], p.getF()[1]);
  }

  if(force != p.getF()){
    p.setOldF(force);
  }
}

template <>
void Boundary<Reflection, 3>::reflect3d(Particle<3>& p) {
  auto reflectionDistance{getReflectionDistance(p)};
  auto force{p.getF()};

  reflect2d(p);

  //Check front & back
  if(borderDirection[4] && (border[2] - p.getX()[2] < reflectionDistance) || borderDirection[5] && (p.getX()[2] < reflectionDistance)){
    p.setF(p.getF()[0], p.getF()[1], -p.getF()[2]);
  }

  if(force != p.getF()){
    p.setOldF(force);
  }
}

template<>
void Boundary<Reflecting, 2>::applyCellProperties(Reflecting& r) {
  for(auto &p : particles){
    reflect2d(p);
  }
}

template<>
void Boundary<Reflecting, 3>::applyCellProperties(Reflecting& r) {
  for(auto &p : particles){
    reflect3d(p);
  }
}


//Smooth Reflection
//TODO: Muss öfter aufgerufen werden
template<size_t dim>
void Boundary<GhostReflection, dim>::ghostReflect2d(Particle<dim>& p) {
  auto reflectionDistance{getReflectionDistance(p)};

  //Reflect?
  Particle<dim> ghost{p};
  //Check top
  if(borderDirection[0] && (border[1] - p.getX()[1] < reflectionDistance)){
    ghost.setX(ghost.getX()[0], border[1] + (border[1]-p.getX()[1]));
  }
  //Check bottom
  if(borderDirection[1] && p.getX()[1] < reflectionDistance)){
    ghost.setX(ghost.getX()[0], - p.getX()[1])
  }
  //Check left
  if(borderDirection[2] && p.getX()[0] < reflectionDistance)){
    ghost.setX(-p.getX()[0], ghost.getX()[1]);
  }
  //Check right
  if(borderDirection[3] && (border[0] - p.getX()[0] < reflectionDistance)){
    ghost.setX(border[0] + (border[0] - p.getX()[0]), ghost.getX()[1]);
  }

  //Calculate force if particles are not at the same position
  if(p.getX() != ghost.getX()){
    ParticleContainer<dim> particleContainer{{p, ghost}};
    calculateF(particleContainer);
    this.addParticle(p);
  }
}

template <>
void Boundary<GhostReflection, 3>::ghostReflect3d(Particle<3>& p) {
  auto reflectionDistance{getReflectionDistance(p)};
  ghostReflect2d(p);

  Particle<dim> ghost{p};

  //Check front
  if(borderDirection[4] && (border[2] - p.getX()[2] < reflectionDistance)){
    ghost.setX(ghost.getX()[0], ghost.getX()[1], border[2] + p.getX()[2]);
  }

  //Check back
  if(borderDirection[5] && p.getX()[2] < reflectionDistance)){
    ghost.setX(ghost.getX()[0], ghost.getX()[1], -p.getX()[2]);
  }

  if(p.getX() != ghost.getX()){
    ParticleContainer<dim> particleContainer{{p, ghost}};
    calculateF(particleContainer);
    this.addParticle(p);
  }
}

template<>
void Boundary<GhostReflection, 2>::applyCellProperties(GhostReflection& r) {
  for(auto &p : particles){
    ghostReflect2d(p);
  }
}

template<>
void Boundary<GhostReflection, 3>::applyCellProperties(GhostReflection& r) {
  for(auto &p : particles){
    ghostReflect3d(p);
  }
}*/