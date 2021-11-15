#pragma once
#include <memory>
#include <arguments/argumentParser/XMLArgumentParser/XMLArgumentParser.h>
#include <arguments/argumentParser/BasicArgumentParser/BasicArgumentParser.h>
#include "ArgumentParser.h"

template<size_t dim>
class ParserStrategy {
 private:
  std::unique_ptr<ArgumentParser<dim>> parser;
 public:

  explicit ParserStrategy(int argc, char *argv[]) {
    if (argc > 1) {
      if (std::string{argv[1]} == "-x" || std::string{argv[1]} == "--xml") {
        parser = std::make_unique<XMLArgumentParser<dim>>(argc, argv);
      } else {
        parser = std::make_unique<BasicArgumentParser<dim>>(argc, argv);
      }
    }
  }

  std::unique_ptr<ArgumentParser<dim>> getParser() {
    return std::move(parser);
  }

  static void showUsage() {
    BasicArgumentParser<dim>::showUsage();
    std::cout << std::endl;
    XMLArgumentParser<dim>::showUsage();
    std::cout << std::endl;
  }
};
