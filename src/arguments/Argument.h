#pragma once
#include <string>
#include <memory>
#include <outputWriter/OutputWriter.h>
/**
 * Argument stores the arguments parsed by ArgumentParser for easy access.
 */
class Argument {

 private:
  std::string inputFileName;
  double end_time;
  double delta_t;
  std::string output;
  std::string writer;
  int iteration;

 public:
  virtual ~Argument() = default;

  /**
  * Argument constructor to construct Arguments provided by the ArgumentParser.
  * @param inputFileName
  * @param end_time
  * @param delta_t
  */
  Argument(std::string inputFileName, double end_time, double delta_t, std::string output,
           std::string writer, double iteration);

  [[nodiscard]] double getEndTime() const;

  [[nodiscard]] double getDeltaT() const;

  [[nodiscard]] std::basic_string<char> getFileName() const;

  [[nodiscard]] int getIteration() const;

  [[nodiscard]] std::basic_string<char> getOutput() const;

  [[nodiscard]] std::basic_string<char> getWriter() const;
};