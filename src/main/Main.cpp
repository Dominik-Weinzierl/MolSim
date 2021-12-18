#include "MolSim.h"



/**
 * Creates a parser which parses information based on the selected parser
 * (e.g. BasicArgumentParser parses arguments from the command line),
 * writes the VTK file and performs the simulation
 * @param argc
 * @param argv
 * @return Program exit code.
 */
int main(int argc, char *argv[]) {
  std::vector<std::string> args(argv + 1, argv + argc);

  /**
   * Specify dimension of simulation. Default: 3D -> flags: -2 or -3
   */
  if (std::find(args.begin(), args.end(), "-2") != args.end()) {
    return MolSim<2>::run(args);
  } else {
    return MolSim<3>::run(args);
  }

}
