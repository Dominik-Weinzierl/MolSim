#pragma once

#include <gtest/gtest.h>
#include <physics/LennardJones/LennardJones.h>

class LennardJonesFixture : public ::testing::Test, public LennardJones<3> {
 protected:
  ParticleContainer<3> container{};
 public:
  LennardJonesFixture() = default;
};
