#pragma once

#include "arguments/argumentParser/ArgumentParser.h"
#include "fileReader/XMLReader/XMLReader.h"

/**
 * Contains status of parsed arguments.
 */
class XMLArgumentStatus : public ArgumentStatus {
 public:
  /**
   * Default constructor.
   */
  XMLArgumentStatus() = default;
};

/**
 * XMLArgumentParser is an parser for arguments via xml configuration file.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class XMLArgumentParser : public ArgumentParser<dim> {
 private:
  /**
   * Status of the provided arguments.
   */
  XMLArgumentStatus status;

 public:
  /**
   * XMLArgumentParser is a constructor that takes arguments provided by the main-method.
   * @param args arguments
   */
  explicit XMLArgumentParser(const std::vector<std::string> &args) : ArgumentParser<dim>(args) {

  }

  /**
   * Validates the arguments.
   * @return true if the arguments are valid, otherwise an exception could be thrown.
   */
  bool validateInput() override {
    for (auto it = this->tokens.begin(); it != this->tokens.end(); ++it) {
      const auto &flag = *it;
      if (it + 1 != this->tokens.end()) {
        const auto &possibleValue = *(it + 1);
        if (flag == "-f" || flag == "--filename") {
          ArgumentParser<dim>::handleFlag(status, "filename", flag, possibleValue);
          it++;
          continue;
        }
      }
      if (flag == "-x" || flag == "--xml" || flag == "-b" || flag == "--benchmark" || flag == "-2" || flag == "-3") {
        continue;
      } else {
        throw std::invalid_argument("Invalid argument: " + flag);
      }
    }
    if (!status.validStatus()) {
      throw std::invalid_argument("Missing required argument. Please check your arguments!");
    }
    return true;
  }

  /**
   * Creates an Argument based on the stored values in the ArgumentStatus.
   * @return std::unique_ptr<Argument<dim>>.
   */
  std::unique_ptr<Argument<dim>> createArgument() override {
    // TODO: Filter requirements
    XMLReader<dim> reader{std::get<std::string>(status.getValue("filename"))};
    return reader.readXML();
  }

  /**
   * Prints the available flag-options.
   */
  void static showUsage() {
    std::stringstream usage;
    usage << "Usage: " << "./MolSim {-x | --xml} {-f | --filename <filename>} [-b | --benchmark] [-2 | -3]" << std::endl;
    usage << "Options:" << std::endl;
    usage << "\t-f,--filename\t\tSpecify the input filename as xml" << std::endl;
    usage << "\t-b,--benchmark\t\tRun simulation as benchmark" << std::endl;
    usage << "\t-2,-3\t\t\tSpecify the dimension of the simulation (default: 3D)" << std::endl;
    std::cout << usage.str();
  }
};

