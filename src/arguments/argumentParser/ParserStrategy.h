#pragma once
#include <memory>
#include <arguments/argumentParser/XMLArgumentParser/XMLArgumentParser.h>
#include <arguments/argumentParser/BasicArgumentParser/BasicArgumentParser.h>
#include "ArgumentParser.h"

/**
 * ParserStrategy selects the ArgumentParser used to parse the input.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class ParserStrategy {
 private:
  /**
   * Stores the used ArgumentParser to parse the provided arguments on different ways.
   */
  std::unique_ptr<ArgumentParser<dim>> parser;
 public:

  /**
   * ParserStrategy constructor selects the ArgumentParser used based on the input.
   * @param argc amount of provided arguments
   * @param argv provided arguments
   */
  explicit ParserStrategy(int argc, char *argv[]) {
    if (argc > 1) {
      // XML prefix available
      if (std::string{argv[1]} == "-x" || std::string{argv[1]} == "--xml") {
        parser = std::make_unique<XMLArgumentParser<dim>>(argc, argv);
      } else {
        parser = std::make_unique<BasicArgumentParser<dim>>(argc, argv);
      }
    }
  }

  /**
   * Getter for ArgumentParser.
   * @return the selected ArgumentParser.
   */
  std::unique_ptr<ArgumentParser<dim>> getParser() {
    return std::move(parser);
  }

  /**
   * Shows usage of available Parser.
   */
  static void showUsage() {
    BasicArgumentParser<dim>::showUsage();
    std::cout << std::endl;
    XMLArgumentParser<dim>::showUsage();
    std::cout << std::endl;
  }
};
