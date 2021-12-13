#pragma once

#include "Thermostat.h"

template<size_t dim>
class DummyThermostat : public Thermostat<dim> {
 public:

  DummyThermostat() : Thermostat<dim>(-1.0, -1.0, -1, -1) {};

  /**
   * Apply the specified thermostat behaviour to a ParticleContainer
   * @param c the ParticleContainer
   */
  void applyThermostat([[maybe_unused]] ParticleContainer<dim> &c) override {}

  /**
   * Sets the initial temperature correctly for particles in the ParticleContainer
   * @param c the ParticleContainer
   */
  void setInitialTemperature([[maybe_unused]] ParticleContainer<dim> &c) override {}

  [[nodiscard]] std::string toString() const override { return ""; };
};