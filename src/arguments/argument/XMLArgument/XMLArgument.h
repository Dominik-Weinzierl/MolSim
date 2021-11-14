#pragma once

#include <generator/GeneratorArguments/CuboidArgument.h>
#include <arguments/argument/Argument.h>
#include <generator/GeneratorArguments/SphereArgument.h>

class XMLArgument : public Argument {
 private:
  std::vector<CuboidArgument> cuboidArguments;
  std::vector<SphereArgument> sphereArguments;

 public:
  XMLArgument(std::vector<CuboidArgument> pCuboidArguments, std::vector<SphereArgument> pSphereArguments,
              std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
              std::string pWriter, int pIteration, std::string pPhysics);

  [[nodiscard]] const std::vector<CuboidArgument>& getCuboidArguments() const;
  [[nodiscard]] const std::vector<SphereArgument>& getSphereArguments() const;

  void createAdditionalParticle(ParticleContainer& container) const override;
};
