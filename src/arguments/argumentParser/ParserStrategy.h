#pragma once

#include <memory>

#include "arguments/argumentParser/XMLArgumentParser/XMLArgumentParser.h"
#include "arguments/argumentParser/BasicArgumentParser/BasicArgumentParser.h"
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

  //----------------------------------------Constructor----------------------------------------

  /**
   * ParserStrategy constructor selects the ArgumentParser used based on the input.
   * @param args arguments
   */
  explicit ParserStrategy(const std::vector<std::string> &args) {
    if (!args.empty()) {
      // XML prefix available
      if (std::string{args[0]} == "-x" || std::string{args[0]} == "--xml") {
        parser = std::make_unique<XMLArgumentParser<dim>>(args);
      } else {
        parser = std::make_unique<BasicArgumentParser<dim>>(args);
      }
    }
  }

  //----------------------------------------Methods----------------------------------------

  /**
   * Shows usage of available Parser.
   */
  static void showUsage() {
    BasicArgumentParser<dim>::showUsage();
    std::cout << std::endl;
    XMLArgumentParser<dim>::showUsage();
    std::cout << std::endl;
  }

  //----------------------------------------Getter & Setter----------------------------------------

  /**
   * Getter for ArgumentParser.
   * @return the selected ArgumentParser.
   */
  std::unique_ptr<ArgumentParser<dim>> getParser() {
    return std::move(parser);
  }
};
