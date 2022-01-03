#include "fstream"
#pragma once

/**
 * Class for writing statistical profiles of a simulation.
 * @tparam dim Dimension of the simulation
 */
template<size_t dim>
class ProfileWriter {

  /**
   * number of bins
   */
  int numOfBins;
  /**
   * number of iterations
   */
  int numOfIterations;
  /**
   * Generate velocity profiles?
   */
  bool velocity;
  /**
   * Generate density profiles?
   */
  bool density;
  /**
   * Domain size
   */
  Vector<dim> dom;
  /**
   * file to write to
   */
  std::ofstream file;

  std::vector<std::vector<Particle<dim>>> particlesIntoBins(ParticleContainer<dim> &c) {
    std::vector<std::vector<Particle<dim>>> bins;
    double xPerBin = dom[0] / static_cast<double>(numOfBins);
    for (auto &p: c) {
      bins[static_cast<int>(p.getX()[0] / xPerBin)].emplace_back(p);
    }
    return bins;
  }

  double computeAverageSpeed(std::vector<Particle<dim>> &b) {
    Vector<dim> ret;
    unsigned long count;
    for (auto &p: b) {
      if (!p.isFixed()) {
        ret = ret + p.getV();
        count++;
      }
    }
    if (count == 0)
      return 0;
    return (ArrayUtils::L2Norm(ret) / static_cast<double>(count));
  }
  double computeDensity(std::vector<Particle<dim>> &b) {
    return b.size();
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
  ProfileWriter(int pBins, int pIter, bool pVel, bool pDens, Vector<dim> pDom) : numOfBins(pBins),
                                                                                 numOfIterations(pIter), velocity(pVel),
                                                                                 density(pDens), dom(pDom) {};
  /**
  * Constructor
  * @param pBins Number of bins
  * @param pIter Number of iterations
  * @param pVel Generate velocity profiles?
  * @param pDens Generate density profiles?
  */
  ProfileWriter(int pBins, int pIter, bool pVel, bool pDens) : numOfBins(pBins), numOfIterations(pIter), velocity(pVel),
                                                               density(pDens) {};

  virtual ~ProfileWriter() = default;

  virtual void generateProfiles(ParticleContainer<dim> &c, int iteration) {
    std::vector<std::vector<Particle<dim>>> bins = particlesIntoBins(c);

    if (velocity) {
      file.open("output/velprofile.csv");
      file << iteration << ";";
      for (auto &b: bins) {
        file << computeAverageSpeed(b) << ";";
      }
      file << std::endl;
      file.close();
    }

    if (density) {
      file.open("output/denprofile.csv");
      file << iteration << ";";
      for (auto &b: bins) {
        file << computeDensity(b) << ";";
      }
      file << std::endl;
      file.close();
    }

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