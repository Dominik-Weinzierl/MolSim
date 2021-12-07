#pragma once

#include <optional>
#include <vector>

#include "arguments/argumentParser/ArgumentParser.h"
#include "arguments/argument/BasicArgument/BasicArgument.h"
#include "outputWriter/XYZWriter/XYZWriter.h"
#include "BasicArgumentParser.h"

/**
 * Contains status of parsed arguments.
 */
class BasicArgumentStatus : public ArgumentStatus {
 public:
  BasicArgumentStatus() : ArgumentStatus() {
    flags.insert({"endTime", {false, "", ""}});
    flags.insert({"deltaT", {false, "", ""}});
    flags.insert({"writer", {true, "default", std::string{"vtk"}}});
    flags.insert({"output", {true, "default", std::string{"MD_vtk"}}});
    flags.insert({"physics", {true, "default", std::string{"gravitation"}}});
    flags.insert({"iteration", {true, "default", 60}});
    flags.insert({"strategy", {true, "default", "DirectSum"}});
  }
};

/**
 * XMLArgumentParser is an parser for arguments via commandline.
 * @tparam dim dimension of our simulation.
 */
template<size_t dim>
class BasicArgumentParser : public ArgumentParser<dim> {
 private:
  /**
   * Status of the provided arguments.
   */
  BasicArgumentStatus status;

 public:

  /**
   * BasicArgumentsParser is a constructor that takes arguments provided by the main-method.
   * @param args arguments
   */
  explicit BasicArgumentParser(const std::vector<std::string> &args) : ArgumentParser<dim>(args) {

  };

  /**
   * Prints the available flag-options.
   */
  void static showUsage() {
    std::stringstream usage;
    usage << "Usage: "
          << "./MolSim [-h | --help] | {-f | --filename} <filename> {-t | --t_end} <t_end> {-d | --delta_t} <delta_t> "
          << "[-o | --output <output>] [-i | --iteration <iteration>] [-w | --writer {vtk | xyz}] [-p | --physics {gravitation | lennard}] [-b | --benchmark] [-2 | -3]"
          << std::endl;
    usage << "Options:" << std::endl;
    usage << "\t-h,--help\t\tShow this help message" << std::endl;
    usage << "\t-f,--filename\t\tSpecify the input filename" << std::endl;
    usage << "\t-t,--t_end\t\tSpecify the end time of this simulation" << std::endl;
    usage << "\t-d,--delta_t\t\tSpecify the time steps per calculation" << std::endl;
    usage << "\t-o,--output\t\tSpecify the output filename" << std::endl;
    usage << "\t-i,--iteration\t\tSpecify the iteration" << std::endl;
    usage << "\t-w,--writer\t\tSpecify the writer used for the output files" << std::endl;
    usage << "\t-p,--physics\t\tSpecify the physics used for the simulation" << std::endl;
    usage << "\t-b,--benchmark\t\tRun simulation as benchmark" << std::endl;
    usage << "\t-2,-3\t\t\tSpecify the dimension of the simulation (default: 3D)" << std::endl;
    std::cout << usage.str();
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
        } else if (flag == "-o" || flag == "--output") {
          ArgumentParser<dim>::handleFlag(status, "output", flag, possibleValue);
          it++;
          continue;
        } else if (flag == "-t" || flag == "--t_end") {
          ArgumentParser<dim>::template handleFlag<double>(status, "endTime", flag, possibleValue);
          it++;
          continue;
        } else if (flag == "-d" || flag == "--delta_t") {
          ArgumentParser<dim>::template handleFlag<double>(status, "deltaT", flag, possibleValue);
          it++;
          continue;
        } else if (flag == "-i" || flag == "--iteration") {
          ArgumentParser<dim>::template handleFlag<int>(status, "iteration", flag, possibleValue);
          it++;
          continue;
        } else if (flag == "-p" || flag == "--physics") {
          ArgumentParser<dim>::handleFlag(status, "physics", flag, possibleValue, {"gravitation", "lennard"});
          it++;
          continue;
        } else if (flag == "-w" || flag == "--writer") {
          ArgumentParser<dim>::handleFlag(status, "writer", flag, possibleValue, {"vtk", "xyz"});
          it++;
          continue;
        }
      }
      if (flag == "-b" || flag == "--benchmark" || flag == "-2" || flag == "-3") {
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
    auto filename = std::get<std::string>(status.getValue("filename"));
    auto endTime = std::get<double>(status.getValue("endTime"));
    auto deltaT = std::get<double>(status.getValue("deltaT"));
    auto output = std::get<std::string>(status.getValue("output"));
    auto writer = std::get<std::string>(status.getValue("writer"));
    auto iteration = std::get<int>(status.getValue("iteration"));
    auto physics = std::get<std::string>(status.getValue("physics"));
    auto strategy = std::get<std::string>(status.getValue("strategy"));

    return std::make_unique<BasicArgument<dim>>(std::vector<std::string>{filename}, endTime, deltaT, output, writer,
                                                iteration, physics, strategy);
  }
};
