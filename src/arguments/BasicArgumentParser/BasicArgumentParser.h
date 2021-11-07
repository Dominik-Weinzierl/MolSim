#pragma once
#include "arguments/ArgumentParser.h"

#include <optional>
#include <vector>

class BasicArgumentStatus : public ArgumentStatus {
 public:
  BasicArgumentStatus();
  bool validStatus() override;
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

  /**
  * Handle end_t flag and sets the status accordingly.
  */
  static void handleEndTimeFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                         const std::string &possibleValue);

  /**
   * Handle end_t flag and sets the status accordingly.
   */
  static void handleDeltaTFlag(BasicArgumentStatus &argumentStatus, const std::string &flag, const std::string &possibleValue);

  /**
   * Handle writer flag and sets the status accordingly.
   */
  static void handleWriterFlag(BasicArgumentStatus &argumentStatus, const std::string &flag, const std::string &possibleValue);

  /**
   * Handle output flag and sets the status accordingly.
   */
  static void handleOutputFlag(BasicArgumentStatus &argumentStatus, const std::string &flag, const std::string &possibleValue);

  /**
   * Handle iteration flag and sets the status accordingly.
   */
  static void handleIterationFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                           const std::string &possibleValue);

  /**
   * Handle physics flag and sets the status accordingly.
   */
  static void handlePhysicsFlag(BasicArgumentStatus &argumentStatus, const std::string &flag,
                                  const std::string &possibleValue);

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
