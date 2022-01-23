#pragma once

#include <ostream>
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

  /**
   * Prints the Force.
   */
  [[nodiscard]] std::string toString() const {
    std::stringstream argument;
    argument << "\t\t\t\t\t\t Force: " << ArrayUtils::to_string(force) << std::endl;
    argument << "\t\t\t\t\t\t Start time: " << startTime << std::endl;
    argument << "\t\t\t\t\t\t End time: " << endTime << std::endl;
    return argument.str();
  };

  /**
   * Stream operator for Force.
   * @param os std::ostream
   * @param f Force
   * @return updated stream
   */
  friend std::ostream &operator<<(std::ostream &os, const Force &f) {
    os << f.toString();
    return os;
  }

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