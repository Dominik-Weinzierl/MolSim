#pragma once

#include <generator/GeneratorArguments/CuboidArgument.h>
#include <arguments/argument/Argument.h>
#include <generator/GeneratorArguments/SphereArgument.h>

template<size_t dim>
class XMLArgument : public Argument<dim> {
 private:
  std::vector<CuboidArgument<dim>> cuboidArguments;
  std::vector<SphereArgument<dim>> sphereArguments;

 public:
  XMLArgument(std::vector<CuboidArgument<dim>> pCuboidArguments, std::vector<SphereArgument<dim>> pSphereArguments,
              std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
              std::string pWriter, int pIteration, std::string pPhysics) : Argument<dim>(std::move(pFiles), pEndTime,
                                                                                         pDeltaT, std::move(pOutput),
                                                                                         std::move(pWriter), pIteration,
                                                                                         std::move(pPhysics)),
                                                                           cuboidArguments{std::move(pCuboidArguments)},
                                                                           sphereArguments{
                                                                               std::move(pSphereArguments)} {

  }

  [[nodiscard]] const std::vector<CuboidArgument<dim>> &getCuboidArguments() const {
    return cuboidArguments;
  }

  [[nodiscard]] const std::vector<SphereArgument<dim>> &getSphereArguments() const {
    return sphereArguments;
  }

  void createAdditionalParticle(ParticleContainer<dim> &container) const override {
    for (const auto &cuboidArgument: getCuboidArguments()) {
      Generator<CuboidArgument<dim>, dim>::generate(cuboidArgument, container);
    }

    for (const auto &sphereArgument: getSphereArguments()) {
      Generator<SphereArgument<dim>, dim>::generate(sphereArgument, container);
    }
  }
};
