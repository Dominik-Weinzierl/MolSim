#include "arguments/ArgumentParser.h"

class BasicArgumentParser : public ArgumentParser {
 private:
  std::vector<std::string> tokens;
  [[nodiscard]] std::optional<std::string> getValueOfArgumentOption(const std::string &option) const;
  [[nodiscard]] bool argumentOptionIsAvailable(const std::string &option) const;
 public:
  explicit BasicArgumentParser(int argc_1, char *arguments_1[]);
  ~BasicArgumentParser();
  ParserStatus validateInput() override;
  Argument createArgument() override;
};
