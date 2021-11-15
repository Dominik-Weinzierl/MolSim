#pragma once
#include "arguments/argumentParser/ArgumentParser.h"
#include "arguments/argument/BasicArgument/BasicArgument.h"
#include "outputWriter/XYZWriter/XYZWriter.h"
#include "BasicArgumentParser.h"

#include <optional>
#include <vector>

class BasicArgumentStatus : public ArgumentStatus {
 public:
  BasicArgumentStatus() : ArgumentStatus() {
    flags.insert({"endTime", {false, "", ""}});
    flags.insert({"deltaT", {false, "", ""}});
    flags.insert({"writer", {true, "default", std::string{"vtk"}}});
    flags.insert({"output", {true, "default", std::string{"MD_vtk"}}});
    flags.insert({"physics", {true, "default", std::string{"gravitation"}}});
    flags.insert({"iteration", {true, "default", 60}});
  }
};

/**
 * BasicArgumentParser is a parser for arguments via commandline.
 */
template<size_t dim>
class BasicArgumentParser : public ArgumentParser<dim> {
 private:
  BasicArgumentStatus status;

 public:

  /**
   * BasicArgumentsParser is a constructor that takes arguments provided by the main-method.
   * @param argc
   * @param arguments
   */
  explicit BasicArgumentParser(int argc, char *arguments[]) : ArgumentParser<dim>(argc, arguments) {

  };

  /**
   * Prints the available flag-options.
   */
  void showUsage() override {
    std::stringstream usage;
    usage << "Usage: " << "./MolSim" << std::endl;
    usage << "Options:" << std::endl;
    usage << "\t-h,--help\t\tShow this help message" << std::endl;
    usage << "\t-f,--filename\t\tSpecify the input filename" << std::endl;
    usage << "\t-t,--t_end\t\tSpecify the end time of this simulation" << std::endl;
    usage << "\t-d,--delta_t\t\tSpecify the time steps per calculation" << std::endl;
    usage << "\t-o,--output\t\tSpecify the output filename" << std::endl;
    usage << "\t-i,--iteration\t\tSpecify the iteration" << std::endl;
    usage << "\t-w,--writer\t\tSpecify the writer used for the output files" << std::endl;
    usage << "\t-p,--physics\t\tSpecify the physics used for the simulation" << std::endl;
    std::cout << usage.str();
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
      } else if (flag == "-o" || flag == "--output") {
        ArgumentParser<dim>::handleFlag(status, "output", flag, possibleValue);
        it++;
      } else if (flag == "-t" || flag == "--t_end") {
        ArgumentParser<dim>::template handleFlag<double>(status, "endTime", flag, possibleValue);
        it++;
      } else if (flag == "-d" || flag == "--delta_t") {
        ArgumentParser<dim>::template handleFlag<double>(status, "deltaT", flag, possibleValue);
        it++;
      } else if (flag == "-i" || flag == "--iteration") {
        ArgumentParser<dim>::template handleFlag<int>(status, "iteration", flag, possibleValue);
        it++;
      } else if (flag == "-p" || flag == "--physics") {
        ArgumentParser<dim>::handleFlag(status, "physics", flag, possibleValue, {"gravitation", "lennard"});
        it++;
      } else if (flag == "-w" || flag == "--writer") {
        ArgumentParser<dim>::handleFlag(status, "writer", flag, possibleValue, {"vtk", "xyz"});
        it++;
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
    auto filename = std::get<std::string>(status.getValue("filename"));
    auto endTime = std::get<double>(status.getValue("endTime"));
    auto deltaT = std::get<double>(status.getValue("deltaT"));
    auto output = std::get<std::string>(status.getValue("output"));
    auto writer = std::get<std::string>(status.getValue("writer"));
    auto iteration = std::get<int>(status.getValue("iteration"));
    auto physics = std::get<std::string>(status.getValue("physics"));

    return std::make_unique<BasicArgument<dim>>(std::vector<std::string>{filename}, endTime, deltaT, output, writer,
                                                iteration, physics);
  }
};
