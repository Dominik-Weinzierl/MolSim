#include "gtest/gtest.h"

#include "thermostat/Thermostat.h"
#include "container/DirectSum/DirectSumContainer.h"

static double eps = std::numeric_limits<double>::epsilon() * 100;

/**
 * Calculates the temperature from the kinetic energy of the container.
 * It is trivial to show the correctness of this naive implementation.
 * @param c A particle container
 * @return The temperature according to the kinetic energy
 */
template<size_t dim>
[[nodiscard]] double kineticEnergyTemp(ParticleContainer<dim> &c) {
  double ret = 0;
  for (auto &p: c) {
    ret += (p.getM() * p.getV() * p.getV()) / 2;
  }
  ret /= static_cast<double >(dim * c.size());
  ret *= 2;
  return ret;
}

/**
* Test that cooling to 0 sets all velocities to zero with no specified deltaT
*/
TEST(Thermostat, zeroDegreesDirect) {
  constexpr static size_t dim = 2;
  DirectSumContainer<dim> container{};
  container.addParticle({{0.5, 0.5}, {42, 69}, 2});
  container.addParticle({{1.5, 0.5}, {-13, 1337}, 2});

  Thermostat<dim> thermostat{42, 0, 0, -1};
  thermostat.applyThermostat(container);
  Vector<dim> zero = {0, 0};
  EXPECT_EQ(container[0].getV(), zero);
  EXPECT_EQ(container[1].getV(), zero);
  EXPECT_NEAR(kineticEnergyTemp(container), 0, eps);
}

/**
* Test that cooling to some other temperature results in the correct temperature with unspecified deltaT
*/
TEST(Thermostat, coolingDirect) {
  constexpr static size_t dim = 2;
  DirectSumContainer<dim> container{};
  container.addParticle({{0.5, 0.5}, {42, 69}, 2});
  container.addParticle({{1.5, 0.5}, {-13, 1337}, 2});

  Thermostat<dim> thermostat{42, 10, 0, -1};
  thermostat.applyThermostat(container);

  EXPECT_NEAR(kineticEnergyTemp(container), 10, eps);
}

/**
* Test that cooling to some other temperature results in the correct temperature with specified deltaT.
*/
TEST(Thermostat, coolingDeltaT) {
  constexpr static size_t dim = 2;
  DirectSumContainer<dim> container{};
  container.addParticle({{0.5, 0.5}, {42, 69}, 2});
  container.addParticle({{1.5, 0.5}, {-13, 1337}, 2});

  Thermostat<dim> thermostat{42, 10, 0, 5};
  double tempBefore = kineticEnergyTemp(container);
  thermostat.applyThermostat(container);

  EXPECT_NEAR(tempBefore - kineticEnergyTemp(container), 5, eps);
}


/**
* Test that heating to some other temperature results in the correct temperature with unspecified deltaT
*/
TEST(Thermostat, heatingDirect) {
  constexpr static size_t dim = 2;
  DirectSumContainer<dim> container{};
  container.addParticle({{0.5, 0.5}, {42, 69}, 2});
  container.addParticle({{1.5, 0.5}, {-13, 1337}, 2});

  Thermostat<dim> thermostat{42, 10000000, 0, -1};
  thermostat.applyThermostat(container);

  EXPECT_NEAR(kineticEnergyTemp(container), 10000000, eps);
}

/**
* Test that heating to some other temperature results in the correct temperature with specified deltaT.
*/
TEST(Thermostat, heatingDeltaT) {
  constexpr static size_t dim = 2;
  DirectSumContainer<dim> container{};
  container.addParticle({{0.5, 0.5}, {4.2, 6.9}, 2});
  container.addParticle({{1.5, 0.5}, {-1.3, 1}, 2});

  Thermostat<dim> thermostat{42, 897150, 0, 5};
  double tempBefore = kineticEnergyTemp(container);
  thermostat.applyThermostat(container);

  EXPECT_NEAR(kineticEnergyTemp(container) - tempBefore, 5, eps);
}


/**
 * Test that the initial temperature of a system without any motion is set correctly.
 */
TEST(Thermostat, initalTNoInitialMotion) {
  constexpr static size_t dim = 2;
  DirectSumContainer<dim> container{};
  container.addParticle({{0.5, 0.5}, {0, 0}, 2});
  container.addParticle({{1.5, 0.5}, {0, 0}, 2});

  Thermostat<dim> thermostat{42, 897150, 0, 5};
  thermostat.setInitialTemperature(container);

  EXPECT_NEAR(kineticEnergyTemp(container), 42, eps);
}

/**
 * Test that the initial temperature of a system with motion is set correctly.
 */
TEST(Thermostat, initalTInitialMotion) {
  constexpr static size_t dim = 2;
  DirectSumContainer<dim> container{};
  container.addParticle({{0.5, 0.5}, {1, 1}, 2});
  container.addParticle({{1.5, 0.5}, {2, 3}, 2});

  Thermostat<dim> thermostat{42, 897150, 0, 5};
  thermostat.setInitialTemperature(container);

  EXPECT_NEAR(kineticEnergyTemp(container), 42, eps);
}
