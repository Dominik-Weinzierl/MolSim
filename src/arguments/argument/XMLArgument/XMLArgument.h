#pragma once

#include <algorithm>
#include <iostream>
#include <utility>
#include <optional>

#include "generator/GeneratorArguments/variants/CuboidArgument.h"
#include "arguments/argument/Argument.h"
#include "generator/GeneratorArguments/SphereArgument.h"
#include "generator/GeneratorArguments/variants/MembraneArgument.h"
#include "generator/GeneratorArguments/RectangularArgument.h"
#include "boundaryType/BoundaryType.h"
#include "thermostat/Thermostat.h"
#include "physics/Forces/ForceContainer.h"

/**
 * XMLArgument stores the arguments parsed by XMLArgumentParser for easy access.
 * @tparam dim dimension of our simulation
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
   * Stores the MembraneArguments(s) used by our Generator to create Membrane(s).
   */
  std::vector<MembraneArgument<dim>> membraneArguments;

  /**
   * Stores the cutoffRadius used by the linked cell algorithm.
   */
  std::optional<double> cutoffRadius;

  /**
   * Stores the domain used by the linked cell algorithm.
   */
  std::optional<Vector<dim>> domain;

  /**
   * Stores the cell size used by the simulation.
   */
  std::optional<Vector<dim>> cellSize;

  /**
   * Stores the used parallelization strategy.
   */
  std::optional<std::string> parallel;

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
   * @param pMembraneArguments arguments used to create Membranes
   * @param pStrategy defines the used strategy for this simulation (direct vs linked cell)
   * @param pCutoffRadius optional cutoff radius used for the linked cell algorithm
   * @param pDomain optional domain used for the linked cell algorithm
   * @param pBoundaries optional boundaries used for the linked cell algorithm
   * @param pCellSize optional cell size used for the linked cell
   * @param pThermostat optional thermostat which is applied during the simulation
   * @param pProfileWriter optional profile writer
   * @param pAdditionalGravitation optional additional gravitation
   * @param pParallel optional parallelization strategy
   */
  XMLArgument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
              std::string pWriter, int pIteration, std::string pPhysics,
              std::vector<CuboidArgument<dim>> pCuboidArguments, std::vector<SphereArgument<dim>> pSphereArguments,
              std::vector<MembraneArgument<dim>> pMembraneArguments, std::string pStrategy,
              std::optional<double> pCutoffRadius, std::optional<Vector<dim>> pDomain,
              std::optional<std::vector<BoundaryType>> pBoundaries, std::optional<Vector<dim>> pCellSize,
              std::unique_ptr<Thermostat<dim>> pThermostat, std::unique_ptr<ProfileWriter<dim>> pProfileWriter,
              Vector<dim> pAdditionalGravitation, std::optional<std::string> pParallel) : Argument<dim>(
      std::move(pFiles), pEndTime, pDeltaT, std::move(pOutput), std::move(pWriter), pIteration, std::move(pPhysics),
      pStrategy, std::move(pThermostat), std::move(pProfileWriter), pAdditionalGravitation), cuboidArguments{
      std::move(pCuboidArguments)}, sphereArguments{std::move(pSphereArguments)}, membraneArguments{pMembraneArguments},
                                                                                          domain{pDomain},
                                                                                          cutoffRadius{pCutoffRadius},
                                                                                          boundaries{
                                                                                              std::move(pBoundaries)},
                                                                                          cellSize{pCellSize}, parallel{
          std::move(pParallel)} {
    SPDLOG_TRACE("XMLArgument created!");
  }

  //----------------------------------------Methods----------------------------------------

  /**
   * Via xml it is possible to define arguments for additional particle generators.
   * @param container the ParticleContainer filled with Particle generated by Generator(s)
   */
  void createAdditionalParticle(ParticleContainer<dim> &container) const override {
    SPDLOG_TRACE("XMLArgument->createAdditionalParticle()");
    // Generate additional Cuboids
    for (const auto &cuboidArgument: getCuboidArguments()) {
      Generator<RectangularArgument<dim>, dim>::generate(cuboidArgument, container);
    }

    // Generate additional Spheres
    for (const auto &sphereArgument: getSphereArguments()) {
      Generator<SphereArgument<dim>, dim>::generate(sphereArgument, container);
    }

    // Generate additional Membranes
    for (const auto &membraneArgument: getMembraneArguments()) {
      Generator<RectangularArgument<dim>, dim>::generate(membraneArgument, container);
    }
  }

  /**
   * Prints the arguments.
   */
  [[nodiscard]] std::string toString() const override {
    SPDLOG_TRACE("XMLArgument->toString()");
    std::stringstream configuration;

    // Print attributes of parent class
    configuration << Argument<dim>::toString();

    // Print additional strategy information if linked cell is used
    if (this->strategy == "LinkedCell") {
      configuration << "\t\tCutoffRadius: " << this->cutoffRadius.value() << std::endl;
      configuration << "\t\tDomain: " << ArrayUtils::to_string(this->domain.value()) << std::endl;
      configuration << "\t\tCell size: " << ArrayUtils::to_string(this->cellSize.value()) << std::endl;
      configuration << "\t\tBoundary: " << ArrayUtils::to_string(this->boundaries.value()) << std::endl;

      if (parallel.has_value()) {
        configuration << "\t\tParallelization: " << parallel.value() << std::endl;
      }
    };

    // Print additional generators
    configuration << "\tGenerator: " << std::endl;

    // Print used cuboid generator
    if (!this->cuboidArguments.empty()) {
      configuration << "\t\tCuboid generator:" << std::endl;
      for (const auto &g: this->cuboidArguments) {
        configuration << g;
      }
    }

    // Print used sphere generator
    if (!this->sphereArguments.empty()) {
      configuration << "\t\tSphere generator:" << std::endl;
      for (const auto &s: this->sphereArguments) {
        configuration << s;
      }
    }

    // Print used membrane generator
    if (!this->membraneArguments.empty()) {
      configuration << "\t\tMembrane generator:" << std::endl;
      for (const auto &m: this->membraneArguments) {
        configuration << m;
      }
    }

    // Print thermostat
    configuration << this->thermostat->toString() << std::endl;

    // Print profile writer
    // configuration << this->profileWriter->toString() << std::endl;

    return configuration.str();
  }

  //----------------------------------------(Un)-Equality-Operator----------------------------------------

  /**
   * Equality operator.
   * @param rhs XMLArgument
   * @return true if the provided XMLArgument has the same values
   */
  bool operator==(const XMLArgument &rhs) const {
    return static_cast<const Argument<dim> &>(*this) == static_cast<const Argument<dim> &>(rhs)
        && cuboidArguments == rhs.cuboidArguments && sphereArguments == rhs.sphereArguments
        && membraneArguments == rhs.membraneArguments && cutoffRadius == rhs.cutoffRadius && domain == rhs.domain
        && cellSize == rhs.cellSize && parallel == rhs.parallel && boundaries == rhs.boundaries;
  }

  /**
   * Inequality operator.
   * @param rhs XMLArgument
   * @return true if the provided XMLArgument has not the same values
   */
  bool operator!=(const XMLArgument &rhs) const {
    return !(rhs == *this);
  }



  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * Updates the cell size at the given index to given cell size.
   * @param index Index at which the cell size Vector should be changed
   * @param pCellSize cell size to update the value of cell size Vector to
   */
  void updateCellSizeOnIndex(size_t index, double pCellSize) {
    cellSize.value()[index] = pCellSize;
  }

  /**
   * Getter for CuboidArguments.
   * @return std::vector of CuboidArguments
   */
  [[nodiscard]] const std::vector<CuboidArgument<dim>> &getCuboidArguments() const {
    SPDLOG_TRACE("XMLArgument->getCuboidArguments(): {}", cuboidArguments.size());
    return cuboidArguments;
  }

  /**
   * Getter for SphereArguments.
   * @return std::vector of SphereArguments
   */
  [[nodiscard]] const std::vector<SphereArgument<dim>> &getSphereArguments() const {
    SPDLOG_TRACE("XMLArgument->getSphereArguments(): {}", sphereArguments.size());
    return sphereArguments;
  }

  /**
   * Getter for MembraneArguments.
   * @return std::vector of MembraneArguments
   */
  [[nodiscard]] const std::vector<MembraneArgument<dim>> &getMembraneArguments() const {
    SPDLOG_TRACE("XMLArgument->getMembraneArguments(): {}", membraneArguments.size());
    return membraneArguments;
  }

  /**
   * Getter for cutoffRadius.
   * @return cutoffRadius
   */
  [[nodiscard]] const std::optional<double> &getCutoffRadius() const {
    SPDLOG_TRACE("XMLArgument->getCutoffRadius(): {}", cutoffRadius.value());
    return cutoffRadius;
  }

  /**
   * Getter for dimension.
   * @return dimension
   */
  [[nodiscard]] const std::optional<Vector<dim>> &getDomain() const {
    SPDLOG_TRACE("XMLArgument->getDomain(): {}", ArrayUtils::to_string(domain.value()));
    return domain;
  }

  /**
   * Getter for boundaries.
   * @return boundaries
   */
  [[nodiscard]] const std::optional<std::vector<BoundaryType>> &getBoundaries() const {
    SPDLOG_TRACE("XMLArgument->getBoundaries(): {}", ArrayUtils::to_string(boundaries.value()));
    return boundaries;
  }

  /**
   * Getter for cell size.
   * @return cellSize
   */
  [[nodiscard]] const std::optional<Vector<dim>> &getCellSize() const {
    SPDLOG_TRACE("XMLArgument->getCellSize(): {}", ArrayUtils::to_string(cellSize.value()));
    return cellSize;
  }

  /**
   * Getter for parallelization.
   * @return cellSize
   */
  [[nodiscard]] const std::optional<std::string> &getParallel() const {
    return parallel;
  }
};
