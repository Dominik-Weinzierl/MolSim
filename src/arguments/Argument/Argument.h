#pragma once
#include <string>

/**
 * Argument stores the arguments parsed by ArgumentParser for easy access.
 */
class Argument {
 private:

  const std::string inputFileName;
  const double end_time;
  const double delta_t;

 public:
  /**
   * Argument constructor to construct Arguments provided by the ArgumentParser.
   * @param inputFileName
   * @param end_time
   * @param delta_t
   */
  Argument(std::string inputFileName, double end_time, double delta_t);

  [[nodiscard]] double getEndTime() const;
  [[nodiscard]] double getDeltaT() const;
  [[nodiscard]] std::basic_string<char> getFileName() const;
};
