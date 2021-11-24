#pragma once
#include "logger/Logger.h"
#include "physics/Physics.h"

/**
 * The Gravitation class is a subclass of Physics and therefore implements the calculation methods
 * for the active force of all particles in the particleContainer.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class Gravitation : public Physics<dim> {
 private:

  /**
   * Updates the force of the Particle(s).
   * @param particleContainer container which contains the Particle(s) used for this simulation.
   */
  void performUpdate(ParticleContainer<dim> &particleContainer) const {
    std::array<double, dim> temp{};
    for (auto i = particleContainer.begin(); i != particleContainer.end(); ++i) {
      for (auto j = i + 1; j != particleContainer.end(); ++j) {
        SPDLOG_TRACE("Calculating force for {} and {}", i->toString(), j->toString());
        double m = i->getM() * j->getM();

        Vector<dim> difference = j->getX() - i->getX();
        double l2Norm = ArrayUtils::L2Norm(difference);

        double factor = m / (l2Norm * l2Norm * l2Norm);

        for (size_t t = 0; t < dim; ++t) {
          temp[t] = factor * difference[t];
        }

        i->updateForce(temp);
        j->updateForce(-temp);
      }
    }
  }
 public:

  /**
   * Calculates the force that is active on all particles via the simple force calculation method.
   * @param particleContainer
   */
  void calculateF(ParticleContainer<dim> &particleContainer) const override {
    SPDLOG_DEBUG("started calculating forces");
    std::array<double, dim> temp{};
    for (auto &p: particleContainer) {
      p.setOldF(p.getF());
      p.setF(temp);
    }
    performUpdate(particleContainer);
    SPDLOG_DEBUG("ended calculating forces");
  }
};