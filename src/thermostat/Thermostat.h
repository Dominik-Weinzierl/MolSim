#pragma once

template<size_t dim>
class Thermostat {
  double initialT;

  /**
   * initialT if not available
   */
  double targetT;

  int numberT;

  /*
   * -1 if not available...
   */
  int deltaT;

  /**
   * Calculates the temperature from the kinetic energy of the container.
   * @param c A particle container
   * @return The temperature according to the kinetic energy
   */
  [[nodiscard]] double kineticEnergyTemp(const ParticleContainer<dim> &c) {
    double ret = 0;
    for (auto &p: c) {
      ret += (p.getM() * p.getV() * p.getV()) / 2;
    }
    ret /= dim * c.size();
    ret *= 2;
    return ret;
  }

 public:
  Thermostat(double pInitialT, double pTargetT, int pNumberT, int pDeltaT) : initialT(pInitialT), targetT(pTargetT),
                                                                             numberT(pNumberT), deltaT(pDeltaT) {}

  bool operator==(const Thermostat &rhs) const {
    return initialT == rhs.initialT && targetT == rhs.targetT && numberT == rhs.numberT && deltaT == rhs.deltaT;

  }

  bool operator!=(const Thermostat &rhs) const {
    return !(rhs == *this);
  }

  /**
   * Prints the Thermostat.
   */
  [[nodiscard]] std::string toString() const {
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

  void applyThermostat(ParticleContainer<dim> &c) {
    auto tcur = kineticEnergyTemp(c);
    if (tcur == targetT)
      return;
    double tnew;
    if (tcur < targetT) {
      if (deltaT == -1) {
        tnew = targetT;
      } else {
        tnew = std::min(targetT - tcur, deltaT);
      }
    }
    if (tcur > targetT) {
      if (deltaT == -1) {
        tnew = targetT;
      } else {
        tnew = std::min(tcur - targetT, deltaT);
      }
    }
    SPDLOG_TRACE("Current temperature: {}, New temperature: {}", tcur, tnew);
    double beta = std::sqrt(tnew / tcur);
    for (auto &p: c) {
      p.setV(beta * p.getV());
    }
  }

  void setInitialTemperature(ParticleContainer<dim> &c) {
    for (auto &p: c) {
      p.setV(maxwellBoltzmannDistributedVelocity<dim>(std::sqrt(initialT / p.getM())));
    }
  }

  [[nodiscard]] int getNumberT() const {
    return numberT;
  }
};