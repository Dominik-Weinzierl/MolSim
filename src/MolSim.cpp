#include "FileReader.h"
#include "MolSim.h"
#include "physics/Physics.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>

int main(int argc, char *argsv[]) {
  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 2) {
    std::cout << "Erroneous programme call! " << std::endl;
    std::cout << "./molsym filename" << std::endl;
  }

  ParticleContainer particleContainer;
  Physics physics;

  FileReader::readFile(particleContainer, argsv[1]);

  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < end_time) {
    // calculate new x
    physics.calculateX(particleContainer);
    // calculate new f
    physics.calculateF(particleContainer);
    // calculate new v
    physics.calculateV(particleContainer);

    iteration++;
    if (iteration % 10 == 0) {
      std::string out_name("MD_vtk");
      outputWriter::XYZWriter::plotParticles(particleContainer, out_name, iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;
    current_time += delta_t;
  }

  std::cout << "output written. Terminating..." << std::endl;
  return 0;
}