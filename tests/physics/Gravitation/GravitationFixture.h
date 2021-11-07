#pragma once

#include <gtest/gtest.h>
#include <physics/Gravitation/Gravitation.h>

class GravitationFixture : public ::testing::Test, public Gravitation {
 protected:
  ParticleContainer container{};
 public:
  GravitationFixture() = default;
};

