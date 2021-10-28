#pragma once
#include <string>
class Argument {
 private:
  const std::string inputFileName;
  const double end_time;
  const double delta_t;

 public:
  Argument(std::string inputFileName, double end_time, double delta_t);
  ~Argument();

  [[nodiscard]] double getEndTime() const;
  [[nodiscard]] double getDeltaT() const;
};
