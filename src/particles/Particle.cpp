#include "Particle.h"

#include <iostream>
#include "utils/ArrayUtils.h"

//---------------------------Constructor---------------------------
Particle::Particle(int type_arg) : f{0., 0., 0.}, old_f{0., 0., 0.}, type{type_arg} {
  std::cout << "Particle generated!" << std::endl;
}

Particle::Particle(const Particle &other) : x{other.x},
                                            v{other.v},
                                            f{other.f},
                                            old_f{other.old_f},
                                            m{other.m},
                                            type{other.type} {
  std::cout << "Particle generated by copy!" << std::endl;
}

Particle::Particle(const Vector &x_arg, const Vector &v_arg,
                   double m_arg, int type_arg) : x{x_arg},
                                                 v{v_arg},
                                                 f{0., 0., 0.},
                                                 old_f{0., 0., 0.},
                                                 m{m_arg},
                                                 type{type_arg} {
  std::cout << "Particle generated!" << std::endl;
}

Particle::~Particle() { std::cout << "Particle destructed!" << std::endl; }

//---------------------------Getter and Setter---------------------------

const Vector &Particle::getX() const { return x; }

const Vector &Particle::getV() const { return v; }

const Vector &Particle::getF() const { return f; }

const Vector &Particle::getOldF() const { return old_f; }

double Particle::getM() const { return m; }

int Particle::getType() const { return type; }

void Particle::setX(const Vector &position) { x = position; }

void Particle::setV(const Vector &velocity) { v = velocity; }

void Particle::setF(const Vector &force) { f = force; }

void Particle::setOldF(const Vector &oldForce) { old_f = oldForce; }

//---------------------------Methods---------------------------

std::string Particle::toString() const {
  std::stringstream stream;
  stream << "Particle: X:" << x << " v: " << v << " f: " << f
         << " old_f: " << old_f << " type: " << type;
  return stream.str();
}

bool Particle::operator==(Particle &other) {
  return (x == other.x) and (v == other.v) and (f == other.f) and
      (type == other.type) and (m == other.m) and (old_f == other.old_f);
}