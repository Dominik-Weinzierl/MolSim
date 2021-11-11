#include "Particle.h"

#include <iostream>
#include <spdlog/spdlog.h>
#include "utils/ArrayUtils.h"

//---------------------------Constructor---------------------------
Particle::Particle(int type_arg) : x{}, v{}, f{}, old_f{}, m{}, type{type_arg} {
  // SPDLOG_INFO("Particle generated");
}

Particle::Particle(const Vector<> &x_arg, const Vector<> &v_arg, double m_arg, int type_arg) : x{x_arg}, v{v_arg}, f{},
                                                                                           old_f{}, m{m_arg},
                                                                                           type{type_arg} {
  // SPDLOG_INFO("Particle generated");
}


//---------------------------Getter and Setter---------------------------

const Vector<> &Particle::getX() const { return x; }

const Vector<> &Particle::getV() const { return v; }

const Vector<> &Particle::getF() const { return f; }

const Vector<> &Particle::getOldF() const { return old_f; }

const double &Particle::getM() const { return m; }

int Particle::getType() const { return type; }

void Particle::setX(const Vector<> &position) { x = position; }

void Particle::setV(const Vector<> &velocity) { v = velocity; }

void Particle::setF(const Vector<> &force) { f = force; }

void Particle::setOldF(const Vector<> &oldForce) { old_f = oldForce; }

//---------------------------Methods---------------------------

std::string Particle::toString() const {
  std::stringstream stream;
  stream << "Particle: X:" << x << " v: " << v << " f: " << f << " old_f: " << old_f << " type: " << type;
  return stream.str();
}

bool Particle::operator==(const Particle &other) {
  return (x == other.x) and (v == other.v) and (f == other.f) and (type == other.type) and (m == other.m)
      and (old_f == other.old_f);
}

std::ostream &operator<<(std::ostream &stream, const Particle &p) {
  stream << p.toString();
  return stream;
}

void Particle::setX(double x_arg, double y_arg, double z_arg) {
  x[0] = x_arg;
  x[1] = y_arg;
  x[2] = z_arg;
}

void Particle::setV(double x_arg, double y_arg, double z_arg) {
  v[0] = x_arg;
  v[1] = y_arg;
  v[2] = z_arg;
}

void Particle::setF(double x_arg, double y_arg, double z_arg) {
  f[0] = x_arg;
  f[1] = y_arg;
  f[2] = z_arg;
}

void Particle::setOldF(double x_arg, double y_arg, double z_arg) {
  old_f[0] = x_arg;
  old_f[1] = y_arg;
  old_f[2] = z_arg;
}

void Particle::updateForce(double x_arg, double y_arg, double z_arg) {
  f[0] += x_arg;
  f[1] += y_arg;
  f[2] += z_arg;
}
