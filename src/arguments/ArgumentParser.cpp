#include <iostream>
#include <sstream>
#include "ArgumentParser.h"
#include <algorithm>

void ArgumentParser::showUsage() {
  std::stringstream usage;
  usage << "Usage: " << "./molsym" << std::endl;
  usage << "Options:" << std::endl;
  usage << "\t-h,--help\t\tShow this help message" << std::endl;
  usage << "\t-f,--filename\t\tSpecify the end time of this simulation" << std::endl;
  usage << "\t-t,--t_end\t\tSpecify the end time of this simulation" << std::endl;
  usage << "\t-d,--delta_t\t\tSpecify the time steps per calculation" << std::endl;
  std::cout << usage.str();
}

