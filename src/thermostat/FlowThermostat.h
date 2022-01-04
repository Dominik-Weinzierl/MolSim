#include "thermostat/Thermostat.h"

/**
 * The thermostat for the nano-flow simulation
 * @tparam dim dimension of the simulation
 */
template<size_t dim>
class FlowThermostat : public Thermostat<dim> {
  /**
   * Calculates the temperature from the kinetic energy of the container.
   * @param c A particle container
   * @return The temperature according to the kinetic energy
   */
  [[nodiscard]] inline double kineticEnergyTemp(ParticleContainer<dim> &c) override {
    double ret = 0;
    double avgYV = 0;
    unsigned long count = 0;
    for (auto &p: c) {
      if (!p.isFixed()) {
        avgYV += p.getV()[1];
        count++;
      }

    }
    avgYV /= static_cast<double>(count);
    for (auto &p: c) {
      Vector<dim> v = p.getV();
      v[1] -= avgYV;
      ret += (p.getM() * v * v) / 2;
    }
    ret /= static_cast<double>(dim * c.size());
    ret *= 2;
    return ret;
  }
/**
 * Apply the special scaling required for nano-flow simulations
 * @param c The particle container on which the scaling should be applied
 * @param beta The factor
 */
  void applyScaling(ParticleContainer<dim> &c, double beta) override;

 public:
  /**
   * Constructor for the thermostat.
   * @param pInitialT initial temperature
   * @param pTargetT target temperature
   * @param pNumberT number of time steps after which the thermostat should be applied
   * @param pDeltaT maximal absolute difference per time step
   */
  FlowThermostat(double pInitialT, double pTargetT, int pNumberT, int pDeltaT) : Thermostat<dim>(pInitialT, pTargetT,
                                                                                                 pNumberT, pDeltaT) {};

};

