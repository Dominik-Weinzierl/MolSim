#include "OutputWriter.h"

#include <utility>
#include <filesystem>

OutputWriter::OutputWriter(std::string fileName, std::string path, const ParticleContainer &container) : fileName{
    std::move(fileName)}, path{std::move(path)}, container{container} {
  if (!std::filesystem::exists(this->path)) {
    std::filesystem::create_directory(this->path);
  }
}
