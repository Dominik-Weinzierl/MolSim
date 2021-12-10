#pragma once

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
};