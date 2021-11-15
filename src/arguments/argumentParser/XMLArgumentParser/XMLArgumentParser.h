#pragma once
#include "arguments/argumentParser/ArgumentParser.h"
#include "fileReader/XMLReader/XMLReader.h"

class XMLArgumentStatus : public ArgumentStatus {
 public:
  XMLArgumentStatus() = default;
};

template<size_t dim>
class XMLArgumentParser : public ArgumentParser<dim> {
 private:
  XMLArgumentStatus status;

 public:
  /**
   * BasicArgumentsParser is a constructor that takes arguments provided by the main-method.
   * @param argc
   * @param arguments
   */
  explicit XMLArgumentParser(int argc, char *arguments[]) : ArgumentParser<dim>(argc, arguments) {

  }

  /**
   * Validates the arguments
   * @return bool
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
   * Creates an Argument via the getValueOfArgumentOption-Method.
   * @return Argument.
   */
  std::unique_ptr<Argument<dim>> createArgument() override {
    XMLReader<dim> reader{std::get<std::string>(status.getValue("filename"))};
    return reader.readXML();
  }

  /**
   * Prints the available flag-options.
   */
  void showUsage() override {
    std::stringstream usage;
    usage << "Usage: " << "./MolSim [-x | --xml]" << std::endl;
    usage << "Options:" << std::endl;
    usage << "\t-h,--help\t\tShow this help message" << std::endl;
    usage << "\t-f,--filename\t\tSpecify the input filename as xml" << std::endl;
    std::cout << usage.str();
  }
};

