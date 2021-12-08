#pragma once

#include <algorithm>
#include <iostream>
#include <utility>
#include <optional>

#include "generator/GeneratorArguments/CuboidArgument.h"
#include "arguments/argument/Argument.h"
#include "generator/GeneratorArguments/SphereArgument.h"
#include "boundaryType/BoundaryType.h"

/**
 * XMLArgument stores the arguments parsed by XMLArgumentParser for easy access.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class XMLArgument : public Argument<dim> {
 private:
  /**
   * Stores the CuboidArgument(s) used by our Generator to create Cuboid(s).
   */
  std::vector<CuboidArgument<dim>> cuboidArguments;

  /**
   * Stores the SphereArgument(s) used by our Generator to create Sphere(s).
   */
  std::vector<SphereArgument<dim>> sphereArguments;

  /**
   * Stores the cutoffRadius used by the linked cell algorithm.
   */
  std::optional<double> cutoffRadius;

  /**
   * Stores the domain used by the linked cell algorithm.
   */
  std::optional<std::array<int, dim>> domain;

  /**
   * Stores the cell size used by the simulation.
   */
  std::optional<std::array<int, dim>> cellSize;

  /**
   * Stores the boundaries used by the linked cell algorithm.
   */
  std::optional<std::vector<BoundaryType>> boundaries;

 public:
  /**
   * XMLArgument constructor to construct Arguments provided by the ArgumentParser (XMLArgumentParser).
   * @param pFiles additional input files to load additional Particle
   * @param pEndTime end time of the simulation
   * @param pDeltaT time steps during the simulation
   * @param pOutput output file prefix
   * @param pWriter used writer to write in the output files
   * @param pIteration defines the writing iteration
   * @param pPhysics defines the used Physics during the simulation
   * @param pCuboidArguments arguments used to create Cuboids
   * @param pSphereArguments arguments used to create Spheres
   * @param pStrategy defines the used strategy for this simulation (direct vs linked cell)
   * @param pCutoffRadius optional cutoff radius used for the linked cell algorithm
   * @param pDomain optional domain used for the linked cell algorithm
   * @param pBoundaries optional boundaries used for the linked cell algorithm
   * @param pCellSize optional cell size used for the linked cell algorithm
   */
  XMLArgument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
              std::string pWriter, int pIteration, std::string pPhysics,
              std::vector<CuboidArgument<dim>> pCuboidArguments, std::vector<SphereArgument<dim>> pSphereArguments,
              std::string pStrategy, std::optional<double> pCutoffRadius, std::optional<std::array<int, dim>> pDomain,
              std::optional<std::vector<BoundaryType>> pBoundaries, std::optional<std::array<int, dim>> pCellSize)
      : Argument<dim>(std::move(pFiles), pEndTime, pDeltaT, std::move(pOutput), std::move(pWriter), pIteration,
                      std::move(pPhysics), pStrategy), cuboidArguments{std::move(pCuboidArguments)},
        sphereArguments{std::move(pSphereArguments)}, domain{pDomain}, cutoffRadius{pCutoffRadius},
        boundaries{std::move(pBoundaries)}, cellSize{pCellSize} {
    SPDLOG_TRACE("XMLArgument created!");
  }

  /**
   * Getter for CuboidArguments.
   * @return std::vector of CuboidArguments.
   */
  [[nodiscard]] const std::vector<CuboidArgument<dim>> &getCuboidArguments() const {
    SPDLOG_TRACE("XMLArgument->getCuboidArguments(): {}", cuboidArguments.size());
    return cuboidArguments;
  }

  /**
   * Getter for SphereArguments.
   * @return std::vector of SphereArguments.
   */
  [[nodiscard]] const std::vector<SphereArgument<dim>> &getSphereArguments() const {
    SPDLOG_TRACE("XMLArgument->getSphereArguments(): {}", sphereArguments.size());
    return sphereArguments;
  }

  /**
   * Getter for cutoffRadius.
   * @return cutoffRadius.
   */
  [[nodiscard]] const std::optional<double> &getCutoffRadius() const {
    SPDLOG_TRACE("XMLArgument->getCutoffRadius(): {}", cutoffRadius.value());
    return cutoffRadius;
  }

  /**
   * Getter for dimension.
   * @return dimension.
   */
  [[nodiscard]] const std::optional<std::array<int, dim>> &getDomain() const {
    SPDLOG_TRACE("XMLArgument->getDomain(): {}", ArrayUtils::to_string(domain.value()));
    return domain;
  }

  /**
   * Getter for boundaries.
   * @return boundaries.
   */
  [[nodiscard]] const std::optional<std::vector<BoundaryType>> &getBoundaries() const {
    SPDLOG_TRACE("XMLArgument->getBoundaries(): {}", ArrayUtils::to_string(boundaries.value()));
    return boundaries;
  }

  /**
   * Getter for cell size.
   * @return cellSize.
   */
  [[nodiscard]] const std::optional<std::array<int, dim>> &getCellSize() const {
    SPDLOG_TRACE("XMLArgument->getCellSize(): {}", ArrayUtils::to_string(cellSize.value()));
    return cellSize;
  }

  /**
   * Via xml it is possible to define arguments for additional particle generators.
   * @param container the ParticleContainer filled with Particle generated by Generator(s)
   */
  void createAdditionalParticle(ParticleContainer<dim> &container) const override {
    SPDLOG_TRACE("XMLArgument->createAdditionalParticle()");
    // CuboidGenerator
    for (const auto &cuboidArgument: getCuboidArguments()) {
      Generator<CuboidArgument<dim>, dim>::generate(cuboidArgument, container);
    }

    // SphereGenerator
    for (const auto &sphereArgument: getSphereArguments()) {
      Generator<SphereArgument<dim>, dim>::generate(sphereArgument, container);
    }
  }

  /**
   * Prints the arguments.
   */
  [[nodiscard]] std::string toString() const override {
    SPDLOG_TRACE("XMLArgument->toString()");
    std::stringstream configuration;
    configuration << Argument<dim>::toString();
    if (this->strategy == "LinkedCell") {
      configuration << "\t\tcutoffRadius: " << this->cutoffRadius.value() << std::endl;
      configuration << "\t\tDomain: " << ArrayUtils::to_string(this->domain.value()) << std::endl;
      configuration << "\t\tBoundary: " << ArrayUtils::to_string(this->boundaries.value()) << std::endl;
    };
    configuration << "\tGenerator: " << std::endl;
    if (!this->cuboidArguments.empty()) {
      configuration << "\t\tCuboid generator:" << std::endl;
      for (const auto &g: this->cuboidArguments) {
        configuration << g;
      }
    }
    if (!this->sphereArguments.empty()) {
      configuration << "\t\tSphere generator:" << std::endl;
      for (const auto &s: this->sphereArguments) {
        configuration << s;
      }
    }

    return configuration.str();
  }
};

/**
 * Compare operator for XMLArgument(s).
 * @tparam dim dimension of simulation
 * @param left first XMLArgument
 * @param right second XMLArgument
 * @return true if all values are equal
 */
template<size_t dim>
bool operator==(const XMLArgument<dim> &left, const XMLArgument<dim> &right) {
  SPDLOG_TRACE("XMLArgument->operator==");
  return left.getCuboidArguments() == right.getCuboidArguments()
      && left.getSphereArguments() == left.getSphereArguments() && left.getFiles() == right.getFiles()
      && left.getEndTime() == right.getEndTime() && left.getDeltaT() == right.getDeltaT()
      && left.getOutput() == right.getOutput() && left.getWriter() == right.getWriter()
      && left.getIteration() == right.getIteration() && left.getPhysics() == right.getPhysics()
      && left.getStrategy() == right.getStrategy() && left.getCutoffRadius() == right.getCutoffRadius()
      && left.getDomain() == right.getDomain() && left.getBoundaries() == right.getBoundaries()
      && left.getCellSize() == right.getCellSize();
}

/**
 * Unequal operator for XMLArgument(s).
 * @tparam dim dimension of simulation
 * @param left first XMLArgument
 * @param right second XMLArgument
 * @return true if on value is unequal.
 */
template<size_t dim>
bool operator!=(const XMLArgument<dim> &left, const XMLArgument<dim> &right) {
  SPDLOG_TRACE("XMLArgument->operator!=");
  return left.getCuboidArguments() != right.getCuboidArguments()
      || left.getSphereArguments() != left.getSphereArguments() || left.getFiles() != right.getFiles()
      || left.getEndTime() != right.getEndTime() || left.getDeltaT() != right.getDeltaT()
      || left.getOutput() != right.getOutput() || left.getWriter() != right.getWriter()
      || left.getIteration() != right.getIteration() || left.getPhysics() != right.getPhysics()
      || left.getStrategy() != right.getStrategy() || left.getCutoffRadius() != right.getCutoffRadius()
      || left.getDomain() != right.getDomain() || left.getBoundaries() != right.getBoundaries()
      || left.getCellSize() != right.getCellSize();
}