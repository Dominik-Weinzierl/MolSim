#include <optional>
#include "arguments/ArgumentParser.h"

class BasicArgumentParser : public ArgumentParser {
 private:
  std::vector<std::string> tokens;
  //! Gives the value of the specified option
  //! \param option the option, for which the value is to be returned
  //! \return the value of the specified option or std::nullopt, if no value was specified
  [[nodiscard]] std::optional<std::string> getValueOfArgumentOption(const std::string &option) const;
  [[nodiscard]] bool argumentOptionIsAvailable(const std::string &option) const;
 public:
  explicit BasicArgumentParser(int argc_1, char *arguments_1[]);
  ~BasicArgumentParser();
  void showUsage() override;
  ParserStatus validateInput() override;
  Argument createArgument() override;
};
