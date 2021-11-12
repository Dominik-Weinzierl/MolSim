#pragma once

#include <memory>
#include "arguments/argument/Argument.h"
#include <tuple>
#include <unordered_map>
#include <variant>

class ArgumentStatus {
 protected:
  std::unordered_map<std::string, std::tuple<bool, std::string, std::variant<std::string, int, double>>> flags;

 public:
  ArgumentStatus();
  /**
   * Destructor generated by the compiler.
   */
  virtual ~ArgumentStatus() = default;
  bool validStatus();

  void updateFlag(const std::string &name, const std::string &flag, std::variant<std::string, int, double> value);

  std::variant<std::string, int, double> getValue(const std::string &name);
};

/**
 * ArgumentParser is an extendable parser for arguments via commandline or configuration file.
 */
class ArgumentParser {
 protected:
  /**
   * Tokens is a Vector of Strings generated by the provided arguments
   */
  std::vector<std::string> tokens;
 public:
  /**
   * BasicArgumentsParser is a constructor that takes arguments provided by the main-method.
   * @param argc
   * @param arguments
   */
  explicit ArgumentParser(int argc, char *arguments[]);

  /**
   * Destructor generated by the compiler.
   */
  virtual ~ArgumentParser() = default;

  /**
   * Creates an Argument via the getValueOfArgumentOption-Method.
   * @return Argument.
   */
  virtual std::unique_ptr<Argument> createArgument() = 0;

  /**
   * Validates the arguments
   * @return bool
   */
  virtual bool validateInput() = 0;

  /**
   * Prints the available flag-options.
   */
  virtual void showUsage() = 0;

  /**
   * Handle the flags and sets the status accordingly without any additional check
   */
  static void handleFlag(ArgumentStatus &status, const std::string &name, const std::string &flag,
                         const std::string &possibleValue);

  /**
   * Handle the flags and sets the status accordingly with additional check
   */
  template<typename T>
  void handleFlag(ArgumentStatus &status, const std::string &name, const std::string &flag,
                  const std::string &possibleValue);

  /**
   * Handle the flags and sets the status accordingly with additional value check
   */
  static void handleFlag(ArgumentStatus &status, const std::string &name, const std::string &flag,
                         const std::string &possibleValue,
                         std::vector<std::string> possibleValues);

  /**
   * Handle the flags and sets the status accordingly with additional check
   */
  template<typename T>
  void performCheck(ArgumentStatus &status, const std::string &name, const std::string &flag,
                    const std::string &possibleValue);
};