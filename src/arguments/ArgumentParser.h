#pragma once

#include "arguments/Argument/Argument.h"

enum ParserStatus {
  Operation_Help, Operation_Simulation, Error_MissingArgument, Error_InvalidOperation,
};

//! ArgumentParser is an extendable parser for arguments via commandline or configuration file
class ArgumentParser {
 public:
  virtual ~ArgumentParser() = default;
  virtual ParserStatus validateInput() = 0;
  virtual Argument createArgument() = 0;
  virtual void showUsage() = 0;
};
