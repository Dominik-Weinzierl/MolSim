#include "OutputWriter.h"

#include <utility>
#include <filesystem>

OutputWriter::OutputWriter(std::string pFileName, std::string pPath, ParticleContainer &pContainer) : fileName{
    std::move(pFileName)}, path{std::move(pPath)}, container{pContainer} {
  if (!std::filesystem::exists(this->path)) {
    std::filesystem::create_directory(this->path);
  }
}
