#pragma once

#include <string>
#include <vector>
#include <optional>
#include "Argument.h"

class ArgumentParser {
 private:
  [[nodiscard]] std::optional<std::string> getValueOfArgumentOption(const std::string &option) const;
  [[nodiscard]] bool argumentOptionIsAvailable(const std::string &option) const;
 public:
  bool validateInput();
  Argument createArgument();
  static void showUsage();
  explicit ArgumentParser(int argc, char *arguments[]);
  ~ArgumentParser();
 private:
  std::vector<std::string> tokens;
};
