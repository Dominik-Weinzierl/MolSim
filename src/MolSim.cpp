#include "FileReader.h"
#include "MolSim.h"
#include "outputWriter/VTKWriter/VTKWriter.h"
#include <iostream>
#include <physics/gravitation/Gravitation.h>

void performSimulation(OutputWriter &&writer, const Physics &physics, ParticleContainer &particleContainer) {
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
      writer.writeFile(iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;
    current_time += delta_t;
  }
}

int main(int argc, char *argv[]) {
  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 2) {
    std::cout << "Erroneous programme call! " << std::endl;
    std::cout << "./molsym filename" << std::endl;
  }
  ParticleContainer particleContainer;
  FileReader::readFile(particleContainer, argv[1]);

  performSimulation(VTKWriter{"MD_vtk", particleContainer}, Gravitation{}, particleContainer);

  std::cout << "output written. Terminating..." << std::endl;

}