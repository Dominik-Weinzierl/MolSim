#pragma once
#include <string>
#include <memory>
#include <outputWriter/OutputWriter.h>
/**
 * Argument stores the arguments parsed by ArgumentParser for easy access.
 */
class Argument {

 private:
  std::vector<std::string> files;
  double end_time;
  double delta_t;
  std::string output;
  std::string writer;
  std::string physics;
  int iteration;

 public:
  virtual ~Argument() = default;

  /**
   * Argument constructor to construct Arguments provided by the ArgumentParser.
   * @param files
   * @param end_time
   * @param delta_t
   * @param output
   * @param writer
   * @param iteration
   * @param physics
   */
  Argument(std::vector<std::string> files, double end_time, double delta_t, std::string output, std::string writer,
           int iteration, std::string physics);

  [[nodiscard]] double getEndTime() const;

  [[nodiscard]] double getDeltaT() const;

  [[nodiscard]] std::vector<std::string> getFiles() const;

  [[nodiscard]] int getIteration() const;

  [[nodiscard]] std::basic_string<char> getOutput() const;

  [[nodiscard]] std::basic_string<char> getWriter() const;

  [[nodiscard]] std::basic_string<char> getPhysics() const;
};