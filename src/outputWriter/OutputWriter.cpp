#include "OutputWriter.h"

#include <utility>
#include <filesystem>

OutputWriter::OutputWriter(std::string fileNameIn, std::string pathIn, ParticleContainer &containerIn) : fileName{
    std::move(fileNameIn)}, path{std::move(pathIn)}, container{containerIn} {
  if (!std::filesystem::exists(this->path)) {
    std::filesystem::create_directory(this->path);
  }
}
