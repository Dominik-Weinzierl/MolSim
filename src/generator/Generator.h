#pragma once

#include "container/ParticleContainer.h"
#include "particles/Particle.h"
#include "generator/GeneratorArguments/RectangularArgument.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "generator/GeneratorArguments/GeneratorArguments.h"

/**
 * Generates shapes based on the provided arguments.
 * @tparam T type of the used GeneratorArguments (e.g. CuboidArguments, SphereArguments, ...)
 * @tparam dim dimension of our simulation.
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<GeneratorArguments<dim>, T>::value,
                                                         bool>::type = true>
class Generator {
 public:

  //----------------------------------------Methods----------------------------------------

  /**
   * Generates shapes and fills the ParticleContainer accordingly.
   * @param g used GeneratorArgument
   * @param container provided particle container
   */
  static void generate(const T &g, ParticleContainer<dim> &container);
  static void generateRectangular(const RectangularArgument<dim> &t, ParticleContainer<dim> &container);
  // If we provide a default implementation, the default implementation is used in all cases. Therefore we have no default implementation here.

 private:

  static void inline linkForce(Particle<dim> &p, const std::vector<ForceContainer<dim>> &forceContainers,
                               std::array<int, dim> index) {
    for (auto &forceContainer: forceContainers) {
      if (!forceContainer.getIndices().empty()) {
        if (std::find(forceContainer.getIndices().begin(), forceContainer.getIndices().end(), index)
            == forceContainer.getIndices().end()) {
          continue;
        }
      }
      p.addAdditionalForce(forceContainer.getForce());
    }
  }

  /**
   * Applies additional temperature/motion to the Particle(s)
   * @param meanValue mean value of the molecules
   * @param p Particle
   */
  static void applyMotion(double meanValue, Particle<dim> &p) {
    Vector<dim> t = p.getV();
    auto max = maxwellBoltzmannDistributedVelocity<dim>(meanValue);
    p.setV(t + max);
  }
};