#pragma once
#include <string>
#include <arguments/Argument.h>

class BasicArgument : public Argument {
 public:
  /**
   * BasicArgument constructor to construct Arguments provided by the ArgumentParser.
   * @param inputFileName
   * @param end_time
   * @param delta_t
   */
  BasicArgument(const std::string &inputFileName, double end_time, double delta_t);
};