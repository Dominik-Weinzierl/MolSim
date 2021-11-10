#pragma once

#include <gtest/gtest.h>
#include <physics/LennardJones/LennardJones.h>

class LennardJonesFixture : public ::testing::Test, public LennardJones {
 protected:
  ParticleContainer container{};
 public:
  LennardJonesFixture() = default;
};
