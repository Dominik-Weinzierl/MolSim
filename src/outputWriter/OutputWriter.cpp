#include "OutputWriter.h"

#include <utility>
OutputWriter::OutputWriter(std::string fileName, const ParticleContainer &container) : fileName{std::move(fileName)},
                                                                                       container{container} {

}
