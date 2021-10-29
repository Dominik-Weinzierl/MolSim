#pragma once

#include <string>
#include <vector>
#include <optional>
#include "Argument.h"

enum ParserStatus {
  Operation_Help, Operation_Simulation, Error_MissingArgument, Error_InvalidOperation,
};

class ArgumentParser {
 private:
  [[nodiscard]] std::optional<std::string> getValueOfArgumentOption(const std::string &option) const;
  [[nodiscard]] bool argumentOptionIsAvailable(const std::string &option) const;
 public:
  ParserStatus validateInput();
  Argument createArgument();
  static void showUsage();
  explicit ArgumentParser(int argc, char *arguments[]);
  ~ArgumentParser();
 private:
  std::vector<std::string> tokens;
};
