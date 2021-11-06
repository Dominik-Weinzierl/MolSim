#pragma once
#include "arguments/ArgumentParser.h"

#include <optional>
#include <vector>

class BasicArgumentStatus : public ArgumentStatus {
 public:
  BasicArgumentStatus() = default;
};

/**
 * BasicArgumentParser is a parser for arguments via commandline.
 */
class BasicArgumentParser : public ArgumentParser {
 private:
  /**
   * Tokens is a Vector of Strings generated by the provided arguments
  */
  std::vector<std::string> tokens;

  BasicArgumentStatus status;

 public:

  /**
   * BasicArgumentsParser is a constructor that takes arguments provided by the main-method.
   * @param argc
   * @param arguments
   */
  explicit BasicArgumentParser(int argc, char *arguments[]);

  /**
   * Prints the available flag-options.
   */
  void showUsage() override;

  /**
  * Validates the arguments
  * @return bool
  */
  bool validateInput() override;

  /**
   * Creates an Argument via the getValueOfArgumentOption-Method.
   * @return Argument.
   */
  std::unique_ptr<Argument> createArgument() override;
};
