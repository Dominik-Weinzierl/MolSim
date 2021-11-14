#pragma once

#include <gtest/gtest.h>
#include <physics/Gravitation/Gravitation.h>

class GravitationFixture : public ::testing::Test, public Gravitation<3> {
 protected:
  ParticleContainer<3> container{};
 public:
  GravitationFixture() = default;
};
