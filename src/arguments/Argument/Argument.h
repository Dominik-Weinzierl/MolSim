#pragma once
#include <string>
class Argument {
 private:
  const std::string inputFileName;
  const double end_time;
  const double delta_t;
  //! Argument stores the arguments for easy access

 public:
  Argument(std::string inputFileName, double end_time, double delta_t);

  [[nodiscard]] double getEndTime() const;
  [[nodiscard]] double getDeltaT() const;
  [[nodiscard]] std::basic_string<char> getFileName() const;

};
