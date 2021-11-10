#pragma once
#include <arguments/argumentParser/ArgumentParser.h>

class XMLArgumentStatus : public ArgumentStatus {
 public:
  XMLArgumentStatus() = default;
};

class XMLArgumentParser : public ArgumentParser {
 private:
  XMLArgumentStatus status;

 public:
  /**
   * BasicArgumentsParser is a constructor that takes arguments provided by the main-method.
   * @param argc
   * @param arguments
   */
  explicit XMLArgumentParser(int argc, char *arguments[]);

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

  /**
   * Prints the available flag-options.
   */
  void showUsage() override;
};

