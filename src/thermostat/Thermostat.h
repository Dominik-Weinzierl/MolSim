#pragma once

#include <cmath>
#include "utils/MaxwellBoltzmannDistribution.h"

template<size_t dim>
class Thermostat {
  double initialT;

  double targetT;

  int numberT;

  int deltaT;

  /**
   * Calculates the temperature from the kinetic energy of the container.
   * @param c A particle container
   * @return The temperature according to the kinetic energy
   */
  [[nodiscard]] double kineticEnergyTemp(ParticleContainer<dim> &c) {
    double ret = 0;
    for (auto &p: c) {
      ret += (p.getM() * p.getV() * p.getV()) / 2;
    }
    ret /= static_cast<double >(dim * c.size());
    ret *= 2;
    return ret;
  }

 public:
  Thermostat(double pInitialT, double pTargetT, int pNumberT, int pDeltaT) : initialT(pInitialT), targetT(pTargetT),
                                                                             numberT(pNumberT), deltaT(pDeltaT) {};

  virtual ~Thermostat() = default;

  bool operator==(const Thermostat &rhs) const {
    return initialT == rhs.initialT && targetT == rhs.targetT && numberT == rhs.numberT && deltaT == rhs.deltaT;

  }

  bool operator!=(const Thermostat &rhs) const {
    return !(rhs == *this);
  }

  /**
   * Prints the Thermostat.
   */
  [[nodiscard]] virtual std::string toString() const {
    std::stringstream argument;
    argument << "\tThermostat: " << std::endl;
    argument << "\t\tInitial temperature: " << initialT << std::endl;
    argument << "\t\tTarget temperature: " << targetT << std::endl;
    argument << "\t\tNumber of time steps: " << numberT << std::endl;
    if (deltaT != -1) {
      argument << "\t\tTemperature difference: " << deltaT << std::endl;
    }
    return argument.str();
  };

  /**
   * Apply the specified thermostat behaviour to a ParticleContainer
   * @param c the ParticleContainer
   */
  virtual void applyThermostat(ParticleContainer<dim> &c) {
    auto tcur = kineticEnergyTemp(c);
    if (tcur == targetT)
      return;
    double tnew;
    if (tcur < targetT) {
      if (deltaT == -1) {
        tnew = targetT;
      } else {
        tnew = std::min(targetT - tcur, static_cast<double>(deltaT));
      }
    }
    if (tcur > targetT) {
      if (deltaT == -1) {
        tnew = targetT;
      } else {
        tnew = std::min(tcur - targetT, static_cast<double>(deltaT));
      }
    }
    SPDLOG_TRACE("Current temperature: {}, New temperature: {}", tcur, tnew);
    double beta = std::sqrt(tnew / tcur);
    for (auto &p: c) {
      p.setV(beta * p.getV());
    }
  }

  /**
   * Sets the initial temperature correctly for particles in the ParticleContainer
   * @param c the ParticleContainer
   */
  virtual void setInitialTemperature(ParticleContainer<dim> &c) {
    for (auto &p: c) {
      p.setV(maxwellBoltzmannDistributedVelocity<dim>(std::sqrt(initialT / p.getM())));
    }
  }

  /**
   * Getter for the number of iterations after which the thermostat should be applied
   * @return The number of simulation iterations per thermostat step.
   */
  [[nodiscard]] int getNumberT() const {
    return numberT;
  }
};