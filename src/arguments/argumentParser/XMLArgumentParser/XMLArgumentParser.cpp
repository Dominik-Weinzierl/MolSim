#include <iostream>
#include "XMLArgumentParser.h"
#include "fileReader/XMLReader/XMLReader.h"

XMLArgumentParser::XMLArgumentParser(int argc, char **arguments) : ArgumentParser(argc, arguments) {

}

bool XMLArgumentParser::validateInput() {
  for (auto it = tokens.begin(); it != tokens.end() && it + 1 != tokens.end(); ++it) {
    const auto &flag = *it;
    const auto &possibleValue = *(it + 1);
    if (flag == "-f" || flag == "--filename") {
      handleFlag(status, "filename", flag, possibleValue);
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

std::unique_ptr<Argument> XMLArgumentParser::createArgument() {
  XMLReader reader{std::get<std::string>(status.getValue("filename"))};
  return reader.readXML();
}

void XMLArgumentParser::showUsage() {
  std::stringstream usage;
  usage << "Usage: " << "./MolSim [-x | --xml]" << std::endl;
  usage << "Options:" << std::endl;
  usage << "\t-h,--help\t\tShow this help message" << std::endl;
  usage << "\t-f,--filename\t\tSpecify the input filename as xml" << std::endl;
  std::cout << usage.str();
}
