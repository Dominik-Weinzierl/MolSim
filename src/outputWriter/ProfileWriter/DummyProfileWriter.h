#include "ProfileWriter.h"

/**
 * Dummy ProfileWriter for simulations not using one.
 * @tparam dim Dimension of the simulation
 */
template<size_t dim>
class DummyProfileWriter : public ProfileWriter<dim> {

 public:
  DummyProfileWriter() : ProfileWriter<dim>(0, 1000, false, false) {};

  void generateProfiles([[maybe_unused]] ParticleContainer<dim> &c, [[maybe_unused]] int iteration) override {};
};