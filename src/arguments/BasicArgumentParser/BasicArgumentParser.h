#pragma once
#include "arguments/ArgumentParser.h"

#include <optional>
#include <vector>

class BasicArgumentParser : public ArgumentParser {
 private:
  std::vector<std::string> tokens;

  //! Gives the value of the specified option
  //! \param option the option, for which the value is to be returned
  //! \return the value of the specified option or std::nullopt, if no value was specified
  [[nodiscard]] std::optional<std::string> getValueOfArgumentOption(const std::string &option) const;
  [[nodiscard]] bool argumentOptionIsAvailable(const std::string &option) const;

 public:
  explicit BasicArgumentParser(int argc, char *arguments[]);
  void showUsage() override;
  ParserStatus validateInput() override;
  Argument createArgument() override;
};
