#include "XYZWriter.h"
#include <sstream>
#include "particles/ParticleContainer.h"
#include <iomanip>
#include <utility>

XYZWriter::XYZWriter(std::string pFileName, std::string pPath, ParticleContainer &pContainer) : OutputWriter(
    std::move(pFileName), std::move(pPath), pContainer) {}

void XYZWriter::plotParticles() {
  auto particles = container.getParticles();
  for (auto &p: particles) {
    auto &x = p.getX();
    file << "Ar ";
    file.setf(std::ios_base::showpoint);
    for (auto &xi: x) {
      file << xi << " ";
    }

    file << std::endl;
  }
}

void XYZWriter::writeFile(int iteration) {
  strStream << path << "/" << fileName << "_" << std::setfill('0') << std::setw(4) << iteration << ".xyz";
  file.open(strStream.str().c_str());
  file << container.getParticles().size() << std::endl;
  file << "Generated by MolSim. See http://openbabel.org/wiki/XYZ_(format) for "
          "file format doku." << std::endl;
  plotParticles();
  file.close();
}
