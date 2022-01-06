#pragma once

template<size_t dim>
class Force {
  /**
   * Force-vector.
   */
  Vector<dim> force;

  /**
   * Start time of force.
   */
  unsigned int startTime;

  /**
   * End time of force.
   */
  unsigned int endTime;

 public:
  /**
   * Constructor for Force.
   * @param pForce force to apply
   * @param pStartTime start time of the force
   * @param pEndTime end time of the force
   */
  Force(Vector<dim> pForce, unsigned int pStartTime, unsigned int pEndTime) : force{pForce}, startTime{pStartTime},
                                                                              endTime{pEndTime} {}

  //----------------------------------------Methods----------------------------------------


  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * Getter for startTime.
   * @return startTime
   */
  [[nodiscard]] unsigned int getStartTime() const {
    return startTime;
  }

  /**
   * Getter for endTime.
   * @return endTime
   */
  [[nodiscard]] unsigned int getEndTime() const {
    return endTime;
  }

  /**
   * Getter for force.
   * @return force
   */
  [[nodiscard]] const Vector<dim> &getForce() const {
    return force;
  }
};