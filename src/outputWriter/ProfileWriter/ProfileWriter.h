#include <utility>

#include "fstream"
#include "container/ParticleContainer.h"
#pragma once

/**
 * Class for writing statistical profiles of a simulation.
 * @tparam dim Dimension of the simulation
 */
template<size_t dim>
class ProfileWriter {

  /**
   * Number of bins.
   */
  int numOfBins;
  /**
   * Number of iterations.
   */
  int numOfIterations;

  /**
   * True if velocity profiles should be generated.
   */
  bool velocity;

  /**
   * True if density profiles should be generated.
   */
  bool density;

  /**
   * Domain size.
   */
  Vector<dim> dom;

  /**
   * File to write to.
   */
  std::ofstream file;

  /**
   * Path to file.
   */
  std::string path;

  /**
   * Sort the particles into bins.
   * @param c the particle container
   * @return a vector of vectors aka bins
   */
  std::vector<std::vector<Particle<dim>>> particlesIntoBins(ParticleContainer<dim> &c) {
    std::vector<std::vector<Particle<dim>>> bins;
    std::vector<Particle<dim>> empty = {};
    for (int i = 0; i < numOfBins; ++i) {
      bins.emplace_back(empty);
    }
    double xPerBin = dom[0] / static_cast<double>(numOfBins);
    for (auto &p: c) {
      bins[static_cast<unsigned long>(p.getX()[0] / xPerBin)].emplace_back(p);
    }
    return bins;
  }

  /**
   * Compute the average speed of a vector of particles.
   * @param b the vector
   * @return the average speed
   */
  double computeAverageSpeed(std::vector<Particle<dim>> &b) {
    Vector<dim> ret{};
    unsigned long count = 0;
    for (auto &p: b) {
      ret = ret + p.getV();
      count++;
    }

    if (count == 0) {
      return 0;
    }

    return (ArrayUtils::L2Norm(ret) / static_cast<double>(count));
  }

  /**
   * Compute the density of a particle vector.
   * @param b the particle vector
   * @return the density
   */
  double computeDensity(std::vector<Particle<2>> &b) {
    return static_cast<double>(b.size()) / (dom[0] / static_cast<double>(numOfBins) * dom[1]);
  }

  /**
   * Compute the density of a particle vector.
   * @param b the particle vector
   * @return the density
   */
  double computeDensity(std::vector<Particle<3>> &b) {
    return static_cast<double>(b.size()) / (dom[0] / static_cast<double>(numOfBins) * dom[1] * dom[2]);
  }

 public:
  /**
   * Constructor
   * @param pBins Number of bins
   * @param pIter Number of iterations
   * @param pVel Generate velocity profiles?
   * @param pDens Generate density profiles?
   * @param pDom domain of the simulation
   */
  ProfileWriter(int pBins, int pIter, bool pVel, bool pDens, Vector<dim> pDom, std::string pPath) : numOfBins(pBins),
                                                                                                     numOfIterations(
                                                                                                         pIter),
                                                                                                     velocity(pVel),
                                                                                                     density(pDens),
                                                                                                     dom(pDom),
                                                                                                     path{std::move(pPath)} {
    // delete already existing files
    if (velocity) {
      std::cout << path << std::endl;

      file.open(path + "velprofile.csv");
      file << "iteration";
      for (int i = 0; i < numOfBins; i++) {
        file << "," << i;
      }
      file << std::endl;
      file.close();
    }
    if (density) {
      file.open(path + "densprofile.csv");
      file << "iteration";
      for (int i = 0; i < numOfBins; i++) {
        file << "," << i;
      }
      file << std::endl;
      file.close();
    }
  };

  /**
   * Destructor
   */
  virtual ~ProfileWriter() = default;

  /**
   * Generate profiles for a given container.
   * @param c the container
   * @param iteration the iteration number (needed for the .csv file)
   */
  virtual void generateProfiles(ParticleContainer<dim> &c, int iteration) {
    std::vector<std::vector<Particle<dim>>> bins = particlesIntoBins(c);

    if (velocity) {
      file.open(path + "velprofile.csv", std::ios::app);
      file << iteration;
      file.setf(std::ios_base::showpoint);
      for (auto &b: bins) {
        file << "," << computeAverageSpeed(b);
      }
      file << std::endl;
      file.close();
    }

    if (density) {
      file.open(path + "densprofile.csv", std::ios::app);
      file << iteration;
      file.setf(std::ios_base::showpoint);
      for (auto &b: bins) {
        file << "," << computeDensity(b);
      }
      file << std::endl;
      file.close();
    }

  }

  /**
   * Equality operator.
   * @param rhs ProfileWriter
   * @return true if the provided ProfileWriter has the same values
   */
  bool operator==(const ProfileWriter &rhs) const {
    return numOfBins == rhs.numOfBins && numOfIterations == rhs.numOfIterations && velocity == rhs.velocity
        && density == rhs.density;
  }

  /**
   * Inequality operator.
   * @param rhs ProfileWriter
   * @return true if the provided ProfileWriter has different values
   */
  bool operator!=(const ProfileWriter &rhs) const {
    return !(rhs == *this);
  }


  //----------------------------------------Getter & Setter----------------------------------------


  /**
   * Getter for the number of iterations after which the profiles should be written
   * @return The number of simulation iterations after which the profiles should be written
   */
  [[nodiscard]] int getNumOfIterations() const {
    return numOfIterations;
  }
};