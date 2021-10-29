#pragma once

#include <string>
#include <vector>
#include <optional>
#include "arguments/Argument/Argument.h"

enum ParserStatus {
  Operation_Help, Operation_Simulation, Error_MissingArgument, Error_InvalidOperation,
};

class ArgumentParser {
 public:
  virtual ParserStatus validateInput() = 0;
  virtual Argument createArgument() = 0;
  static void showUsage();
 private:
};
