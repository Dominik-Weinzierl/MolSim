#pragma once

#include <cmath>
#include "iostream"
#include "container/ParticleContainer.h"
#include "utils/MaxwellBoltzmannDistribution.h"

/**
 * The thermostat as introduced on worksheet 4.
 * @tparam dim Dimension of the simulation
 */
template<size_t dim>
class Thermostat {
  /**
   * Initial temperature.
   */
  double initialT;

  /**
   * Target temperature.
   */
  double targetT;

  /**
   * Number of time steps, after which the thermostat should be applied.
   */
  int numberT;

  /**
   * Maximal absolute temperature difference per time step.
   */
  int deltaT;

  //----------------------------------------Methods----------------------------------------

  /**
   * Calculates the temperature from the kinetic energy of the container.
   * @param c A particle container
   * @return The temperature according to the kinetic energy
   */
  [[nodiscard]] virtual inline double kineticEnergyTemp(ParticleContainer<dim> &c) {
    double ret = 0;
    for (auto &p: c) {
      ret += (p.getM() * p.getV() * p.getV()) / 2;
    }
    ret /= static_cast<double >(dim * c.size());
    ret *= 2;
    return ret;
  }

  /**
   * Calculate the scaling factor.
   * @param currentTemp The current temperature of the system
   * @param targetTemp The target temperature of the system
   * @param pDeltaT The absolute maximum temperature difference per timestep
   * @return
   */
  [[nodiscard]] inline double calculateBeta(double currentTemp, double targetTemp, double pDeltaT) {
    if (currentTemp == targetTemp)
      return 1;

    double difference = currentTemp - targetTemp;

    if (pDeltaT != -1) {
      if (difference < 0) {
        pDeltaT *= -1;
      }
      if (difference < 0)
        difference = std::max(difference, pDeltaT);
      else
        difference = std::min(difference, pDeltaT);
    }

    return std::sqrt((currentTemp - difference) / currentTemp);
  }

  /**
   * Apply the specified thermostat behaviour to a ParticleContainer.
   * @param c the ParticleContainer
   */
  void applyInitialThermostat(ParticleContainer<dim> &c) {
    auto currentTemp = kineticEnergyTemp(c);
    double beta = calculateBeta(currentTemp, initialT, -1);
    applyScaling(c, beta);
  }

  /**
 * Apply the scaling.
 * @param c The particle container on which the scaling should be applied
 * @param beta The factor
 */
  virtual void applyScaling(ParticleContainer<dim> &c, double beta) {
    for (auto &p: c) {
      p.setV(beta * p.getV());
    }
  }

 public:

  //----------------------------------------Constructor & Destructor----------------------------------------

  /**
   * Constructor for the thermostat.
   * @param pInitialT initial temperature
   * @param pTargetT target temperature
   * @param pNumberT number of time steps after which the thermostat should be applied
   * @param pDeltaT maximal absolute difference per time step
   */
  Thermostat(double pInitialT, double pTargetT, int pNumberT, int pDeltaT) : initialT(pInitialT), targetT(pTargetT),
                                                                             numberT(pNumberT), deltaT(pDeltaT) {};

  virtual ~Thermostat() = default;


  //----------------------------------------Methods----------------------------------------

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
   * Apply the specified thermostat behaviour to a ParticleContainer.
   * @param c the ParticleContainer
   */
  virtual void applyThermostat(ParticleContainer<dim> &c) {
    auto currentTemp = kineticEnergyTemp(c);
    double beta = calculateBeta(currentTemp, targetT, deltaT);
    applyScaling(c, beta);
  }

  /**
   * Sets the initial temperature correctly for particles in the ParticleContainer.
   * @param c the ParticleContainer
   */
  virtual void setInitialTemperature(ParticleContainer<dim> &c) {
    bool allZero = true;
    for (Particle<dim> &p: c) {
      for (size_t i = 0; i < dim; ++i) {
        if (p.getV()[i] != 0) {
          allZero = false;
          break;
        }
      }
    }
    if (allZero) {
      SPDLOG_WARN("All velocities were zero. They will be initialized with default values");
      std::cout << "All velocities were zero. They will be initialized with default values" << std::endl;
      for (Particle<dim> &p: c) {
        p.setV(maxwellBoltzmannDistributedVelocity<dim>(std::sqrt(initialT / p.getM())));
      }
    }
    applyInitialThermostat(c);

  }

  //----------------------------------------(Un)-Equality operator----------------------------------------

  /**
   * Equality operator.
   * @param rhs an other thermostat
   * @return true iff the two thermostats are identical
   */
  bool operator==(const Thermostat &rhs) const {
    return initialT == rhs.initialT && targetT == rhs.targetT && numberT == rhs.numberT && deltaT == rhs.deltaT;
  }

  /**
   * Inequality operator.
   * @param rhs an other thermostat
   * @return true if the two thermostats are not identical
   */
  bool operator!=(const Thermostat &rhs) const {
    return !(rhs == *this);
  }

  //----------------------------------------Getter & Setter----------------------------------------


  /**
   * Getter for the number of iterations after which the thermostat should be applied.
   * @return The number of simulation iterations per thermostat step
   */
  [[nodiscard]] int getNumberT() const {
    return numberT;
  }

  /**
   * Getter for the target temperature.
   * @return The targetTemperature
   */
  [[nodiscard]] double getTargetT() const {
    return targetT;
  }
};