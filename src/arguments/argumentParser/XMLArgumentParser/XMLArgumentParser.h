#pragma once

#include "arguments/argumentParser/ArgumentParser.h"
#include "fileReader/XMLReader/XMLReader.h"

/**
 * Contains status of parsed arguments.
 */
class XMLArgumentStatus : public ArgumentStatus {
 public:

  //----------------------------------------Constructor----------------------------------------

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

  /**
   *
   */
  double scaleToSelectedPrecision(double d, double &p) {
    return std::floor(d / p + 0.5) * p;
  }

 public:

  //----------------------------------------Constructor----------------------------------------

  /**
   * XMLArgumentParser is a constructor that takes arguments provided by the main-method.
   * @param args arguments
   */
  explicit XMLArgumentParser(const std::vector<std::string> &args) : ArgumentParser<dim>(args) {
    SPDLOG_TRACE("XMLArgumentParser created!");
  }

  //----------------------------------------Methods----------------------------------------

  /**
   * Validates the arguments.
   * @return true if the arguments are valid, otherwise an exception could be thrown.
   */
  bool validateInput() override {
    SPDLOG_TRACE("XMLArgumentParser->validateInput(): {}", ArrayUtils::to_string(this->tokens));
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
    SPDLOG_TRACE("XMLArgumentParser->createArgument()");
    XMLReader<dim> reader{std::get<std::string>(status.getValue("filename"))};
    std::unique_ptr<XMLArgument<dim>> arg = reader.readXML();

    if (arg->getStrategy() == "LinkedCell") {
      double precision = 0.01;

      // Check Domain is multiple of Cell size
      std::array<std::vector<double>, dim> possibleCellSizesForAllDimension;

      for (size_t i = 0; i < dim; ++i) {
        if (std::fmod(arg->getDomain().value()[i], arg->getCellSize().value()[i]) >= 0.0001) {
          int multiple = static_cast<int>(arg->getDomain().value()[i] / arg->getCellSize().value()[i]);
          double newCellSize = arg->getDomain().value()[i] / static_cast<double>(multiple);
          double preciseNewCellSize = scaleToSelectedPrecision(newCellSize, precision);
          std::vector<double> possibleCellSizes;

          if (preciseNewCellSize * multiple != arg->getDomain().value()[i]) {
            for (int m = multiple - 1; m <= multiple + 1; m++) {
              for (int j = -100; j <= 100; ++j) {
                double possibleCellSize = scaleToSelectedPrecision(preciseNewCellSize + (j * 0.01), precision);
                if (scaleToSelectedPrecision(possibleCellSize * m, precision) == arg->getDomain().value()[i]) {
                  possibleCellSizes.push_back(possibleCellSize);
                }
              }
            }
            if (possibleCellSizes.empty()) {
              throw std::invalid_argument(
                  "Sadly I wasn't able to find a suitable cell size for your domain in dimension "
                      + std::to_string(i));
            }
            possibleCellSizesForAllDimension[i] = possibleCellSizes;
          }
        }
      }

      if (!std::all_of(possibleCellSizesForAllDimension.begin(), possibleCellSizesForAllDimension.end(), [](auto &v) {
        return v.empty();
      })) {
        for (size_t i = 0; i < dim; ++i) {
          if (!possibleCellSizesForAllDimension[i].empty()) {
            std::cout << "Dimension " << i << ": " << ArrayUtils::to_string(possibleCellSizesForAllDimension[i])
                      << std::endl;
          }
        }
        throw std::invalid_argument(
            "Please select one of the provided values for your new cell size or check for other suitable cell sizes");
      }

      // Check we have at least three Cells per Dimension
      for (size_t i = 0; i < dim; ++i) {
        if (arg->getDomain().value()[i] / arg->getCellSize().value()[i] < 3) {
          throw std::invalid_argument("At least three cells per dimension are needed");
        }
      }

      // Check boundary conditions
      for (size_t i = 0; i < dim; ++i) {
        if ((arg->getBoundaries().value()[i * 2] == BoundaryType::Periodic
            && arg->getBoundaries().value()[(i * 2) + 1] != BoundaryType::Periodic)
            || (arg->getBoundaries().value()[i * 2] != BoundaryType::Periodic
                && arg->getBoundaries().value()[(i * 2) + 1] == BoundaryType::Periodic)) {
          throw std::invalid_argument(
              "Opposite sides needs to be both periodic or any other boundary condition! Mixing periodic with other boundary conditions is not possible!");
        }
      }
    }

    return arg;
  }

  /**
   * Prints the available flag-options.
   */
  void static showUsage() {
    SPDLOG_TRACE("XMLArgumentParser->showUsage()");
    std::stringstream usage;
    usage << "Usage: " << "./MolSim {-x | --xml} {-f | --filename <filename>} [-b | --benchmark] [-2 | -3]"
          << std::endl;
    usage << "Options:" << std::endl;
    usage << "\t-f,--filename\t\tSpecify the input filename as xml" << std::endl;
    usage << "\t-b,--benchmark\t\tRun simulation as benchmark" << std::endl;
    usage << "\t-2,-3\t\t\tSpecify the dimension of the simulation (default: 3D)" << std::endl;
    std::cout << usage.str();
  }
};
