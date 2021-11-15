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
   * @param argc amount of provided arguments
   * @param arguments provided arguments
   */
  explicit XMLArgumentParser(int argc, char *arguments[]) : ArgumentParser<dim>(argc, arguments) {

  }

  /**
   * Validates the arguments.
   * @return true if the arguments are valid, otherwise an exception could be thrown.
   */
  bool validateInput() override {
    for (auto it = this->tokens.begin(); it != this->tokens.end() && it + 1 != this->tokens.end(); ++it) {
      const auto &flag = *it;
      const auto &possibleValue = *(it + 1);
      if (flag == "-f" || flag == "--filename") {
        ArgumentParser<dim>::handleFlag(status, "filename", flag, possibleValue);
        it++;
      } else if (flag == "-x" || flag == "--xml") {
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
    XMLReader<dim> reader{std::get<std::string>(status.getValue("filename"))};
    return reader.readXML();
  }

  /**
   * Prints the available flag-options.
   */
  void static showUsage() {
    std::stringstream usage;
    usage << "Usage: " << "./MolSim [-x | --xml] {-f | --filename <filename>}" << std::endl;
    usage << "Options:" << std::endl;
    usage << "\t-f,--filename\t\tSpecify the input filename as xml" << std::endl;
    std::cout << usage.str();
  }
};

