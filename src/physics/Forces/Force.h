#pragma once

/**
 * Wrapper for xsd-force_t.
 * @tparam dim dimension of the Vectors
 */
template<size_t dim>
class Force {
 private:

  /**
   * Vector of indices.
   * Empty if force should be applied to all particles.
   */
  std::vector<Vector<dim>> indices;

  /**
  * Vector of particle-pointers.
  */
  std::vector<Particle<dim> *> additionalForceParticles{};

  /**
   * Force-vector.
   */
  Vector<dim> force;

  /**
   * Start time of force.
   */
  long long unsigned int startTime;

  /**
   * End time of force.
   */
  long long unsigned int endTime;

 public:

  /**
   * Constructor for Force.
   * @param pIndices indices to apply force to
   * @param pForce force to apply
   * @param pStartTime start time of the force
   * @param pEndTime end time of the force
   */
  Force(std::vector<Vector<dim>> pIndices,
        Vector<dim> pForce,
        long long unsigned int pStartTime,
        long long unsigned int pEndTime) : indices{pIndices}, force{pForce}, startTime{pStartTime}, endTime{pEndTime} {}

  /**
   * Adds a particle to additionalForceParticles.
   * @param a Vector of particle-pointers
   */
  void addAdditionalForceParticles(Particle<dim> *a){
    additionalForceParticles.template emplace_back(a);
  }

  /**
   * Getter for startTime.
   * @return startTime
   */
  [[nodiscard]] long long unsigned int getStartTime() const {
    return startTime;
  }

  /**
   * Getter for endTime.
   * @return endTime
   */
  [[nodiscard]] long long unsigned int getEndTime() const {
    return endTime;
  }

  /**
   * Getter for indices.
   * @return indices
   */
  [[nodiscard]] const std::vector<Vector<dim>> &getIndices() const {
    return indices;
  }

  /**
   * Getter for additionalForceParticles.
   * @return additionalForceParticles.
   */
  [[nodiscard]] const std::vector<Particle<dim> *> &getAdditionalForceParticles() const {
    return additionalForceParticles;
  }

  /**
   * Getter for force.
   * @return force
   */
  [[nodiscard]] const Vector<dim> &getForce() const {
    return force;
  }
};