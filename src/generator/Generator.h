#pragma once

#include "container/ParticleContainer.h"
#include "particles/Particle.h"
#include "generator/GeneratorArguments/RectangularArgument.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "generator/GeneratorArguments/GeneratorArguments.h"
#include "generator/GeneratorArguments/variants/MembraneArgument.h"

/**
 * Generates shapes based on the provided arguments.
 * @tparam T type of the used GeneratorArguments (e.g. CuboidArguments, SphereArguments, ...)
 * @tparam dim dimension of our simulation.
 */
template<typename T, size_t dim, typename std::enable_if<std::is_base_of<GeneratorArguments<dim>, T>::value,
                                                         bool>::type = true>
class Generator {
  //----------------------------------------Methods----------------------------------------

  /**
   * Links the force that is additional applied on this Particle p.
   * @param p Particle
   * @param forceContainers additional forces
   * @param index of Particle in structure
   */
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
   * Applies additional temperature/motion to the Particle(s).
   * @param meanValue mean value of the molecules
   * @param p Particle
   */
  static void applyMotion(double meanValue, Particle<dim> &p) {
    Vector<dim> t = p.getV();
    auto max = maxwellBoltzmannDistributedVelocity<dim>(meanValue);
    p.setV(t + max);
  }

  /**
   * Helper method to create Cuboid(s) and Membrane(s).
   * @param t argument which provides all necessary information
   * @param container where the Particle are stored
   */
  static void generateRectangular(const RectangularArgument<dim> &t, ParticleContainer<dim> &container);

  /**
   * Sets the outline of the Membrane fix.
   * @param zero start index of Particles in the container
   * @param m argument which is used to create the membrane
   * @param container where the Particle are stored
   */
  static void fixOutline(int zero, const MembraneArgument<dim> &m, ParticleContainer<dim> &container);

  /**
   * Sets the Particle on position fixed.
   * @param pos index in list
   * @param container where the Particle are stored
   */
  static void setFixed(int pos, ParticleContainer<dim> &container) {
    if (pos == -1) {
      return;
    }

    Particle<dim> &p = container.getParticles()[static_cast<unsigned long>(pos)];
    p.setV(Vector<dim>{});
    p.setFixed(true);
  }

 public:

  //----------------------------------------Methods----------------------------------------

  /**
   * Generates shapes and fills the ParticleContainer accordingly.
   * @param g used GeneratorArgument
   * @param container provided particle container
   */
  static void generate(const T &g, ParticleContainer<dim> &container);

  /**
   * Gets position of Particle (in detail a Molecule) in the list of Particle(s).
   * @param index index in membrane
   * @param zero start index of membrane molecules in Particle list
   * @param c argument to create the membrane
   * @return position in list as int
   */
  static int getPositionInContainer(std::array<int, dim> index, int zero, const RectangularArgument<dim> &c);
};
