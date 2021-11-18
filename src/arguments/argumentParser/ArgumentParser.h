#pragma once

#include <memory>
#include "arguments/argument/Argument.h"
#include <tuple>
#include <unordered_map>
#include <utility>
#include <variant>

/**
 * Contains status of parsed arguments.
 */
class ArgumentStatus {
 protected:
  /**
   * Stores our flags with additional values and default values for easy access.
   */
  std::unordered_map<std::string, std::tuple<bool, std::string, std::variant<std::string, int, double>>> flags;

 public:

  /**
   * Insert available arguments during construction.
   */
  ArgumentStatus() {
    flags.insert({"filename", {false, "", ""}});
  }

  /**
   * Destructor generated by the compiler.
   */
  virtual ~ArgumentStatus() = default;

  /**
   * Used to verify the input. All required flags and values needs to be available.
   * @return
   */
  bool validStatus() {
    return std::all_of(flags.begin(), flags.end(), [](auto v) {
      return std::get<0>(std::get<1>(v));
    });
  }

  /**
   * Sets the correct flag values.
   * @param name flag name
   * @param flag used flag (e.g. -f instead of --filename)
   * @param value corresponding input value
   */
  void updateFlag(const std::string &name, const std::string &flag, std::variant<std::string, int, double> value) {
    std::get<0>(flags[name]) = true;
    std::get<1>(flags[name]) = flag;
    std::get<2>(flags[name]) = std::move(value);
  }

  /**
   * Getter for flag value.
   * @param name flag name
   * @return value of the corresponding flag.
   */
  std::variant<std::string, int, double> getValue(const std::string &name) {
    return std::get<2>(flags[name]);
  }
};

/**
 * ArgumentParser is an extendable parser for arguments via commandline or configuration file.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class ArgumentParser {
 protected:
  /**
   * Tokens is a Vector of Strings generated by the provided arguments.
   */
  std::vector<std::string> tokens;
 public:
  /**
   * BasicArgumentsParser is a constructor that takes arguments provided by the main-method.
   * @param args arguments
   */
  explicit ArgumentParser(std::vector<std::string> args) : tokens{std::move(args)} {

  }

  /**
   * Destructor generated by the compiler.
   */
  virtual ~ArgumentParser() = default;

  /**
   * Creates an Argument based on the stored values in the ArgumentStatus.
   * @return std::unique_ptr<Argument<dim>>.
   */
  virtual std::unique_ptr<Argument<dim>> createArgument() = 0;

  /**
   * Validates the arguments
   * @return bool
   */
  virtual bool validateInput() = 0;

  /**
   * Handle the flags and sets the status accordingly without any additional check
   * @param status ArgumentStatus which stores the flags
   * @param name name of the flag
   * @param flag used flag
   * @param possibleValue possible values of the flag (which must not be checked)
   */
  static void handleFlag(ArgumentStatus &status, const std::string &name, const std::string &flag,
                         const std::string &possibleValue) {
    status.updateFlag(name, flag, possibleValue);
  }

  /**
   * Handle the flags and sets the status accordingly with additional check
   * @tparam T required type (e.g. flag value needs to be a double)
   * @param status ArgumentStatus which stores the flags
   * @param name name of the flag
   * @param flag used flag
   * @param possibleValue possible values of the flag (which must be checked)
   */
  template<typename T>
  void handleFlag(ArgumentStatus &status, const std::string &name, const std::string &flag,
                  const std::string &possibleValue) {
    performCheck<T>(status, name, flag, possibleValue);
  }

  /**
   * Handle the flags and sets the status accordingly with additional check and limited possible values.
   * @param status ArgumentStatus which stores the flags
   * @param name name of the flag
   * @param flag used flag
   * @param possibleValue possible values of the flag (which must be checked)
   * @param possibleValues allowed values
   */
  static void handleFlag(ArgumentStatus &status, const std::string &name, const std::string &flag,
                         const std::string &possibleValue, std::vector<std::string> possibleValues) {
    if (std::find(possibleValues.begin(), possibleValues.end(), possibleValue) == possibleValues.end()) {
      throw std::invalid_argument("Expected: " + ArrayUtils::to_string(possibleValues) + " | Got: " + possibleValue);
    }
    status.updateFlag(name, flag, possibleValue);
  }

  /**
   * Performs additional checks for the flags.
   * @tparam T required type (e.g. flag value needs to be a double)
   * @param status ArgumentStatus which stores the flags
   * @param name name of the flag
   * @param flag used flag
   * @param possibleValue possible values of the flag (which must be checked)
   */
  template<typename T>
  void performCheck(ArgumentStatus &status, const std::string &name, const std::string &flag,
                    const std::string &possibleValue);

};