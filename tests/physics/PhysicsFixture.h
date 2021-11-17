#pragma once

#include <gtest/gtest.h>
#include <physics/Physics.h>

class PhysicsFixture : public ::testing::Test, public Physics<3> {
 protected:
  ParticleContainer<3> container{};

  /**
   * Not used.
   * @param particleContainer
   */
  void calculateF([[maybe_unused]] ParticleContainer<3> &particleContainer) const override {};
 public:
  PhysicsFixture() = default;
};
