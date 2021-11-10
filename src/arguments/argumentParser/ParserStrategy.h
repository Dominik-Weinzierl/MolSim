#pragma once
#include <memory>
#include "ArgumentParser.h"

class ParserStrategy {
 private:
  std::unique_ptr<ArgumentParser> parser;
 public:
  explicit ParserStrategy(int argc, char *argv[]);

  std::unique_ptr<ArgumentParser> getParser();

  static void showUsage();
};
