#pragma once
#include <string>
#include <arguments/argument/Argument.h>

class BasicArgument : public Argument {
 public:
  /**
   * BasicArgument constructor to construct Arguments provided by the ArgumentParser.
   * @param filesIn
   * @param end_timeIn
   * @param delta_tIn
   * @param outputIn
   * @param writerIn
   * @param iterationIn
   * @param physicsIn
   */
  BasicArgument(std::vector<std::string> filesIn,
                double end_timeIn,
                double delta_tIn,
                std::string outputIn,
                std::string writerIn,
                int iterationIn,
                std::string physicsIn);
};
