#pragma once
#include <string>
#include <arguments/argument/Argument.h>

class BasicArgument : public Argument {
 public:
  /**
   * BasicArgument constructor to construct Arguments provided by the ArgumentParser.
   * @param pFiles
   * @param pEndTime
   * @param pDeltaT
   * @param pOutput
   * @param pWriter
   * @param pIteration
   * @param pPhysics
   */
  BasicArgument(std::vector<std::string> pFiles, double pEndTime, double pDeltaT, std::string pOutput,
                std::string pWriter, int pIteration, std::string pPhysics);
};
