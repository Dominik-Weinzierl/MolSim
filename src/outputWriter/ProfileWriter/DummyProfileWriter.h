#include "ProfileWriter.h"

/**
 * Dummy ProfileWriter for simulations not using one.
 * @tparam dim Dimension of the simulation
 */
template<size_t dim>
class DummyProfileWriter : public ProfileWriter<dim> {

 public:
  /**
   * Constructor, calls constructor of superclass ProfileWriter.
   */
  explicit DummyProfileWriter() : ProfileWriter<dim>(0, 1000, false, false, {}, "output") {};

  /**
   * Generate profiles for a given container.
   * @param c the container
   * @param iteration the iteration number (needed for the .csv file)
   */
  void generateProfiles([[maybe_unused]] ParticleContainer<dim> &c, [[maybe_unused]] int iteration) override {};
};