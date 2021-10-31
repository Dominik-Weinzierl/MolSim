#include "OutputWriter.h"

#include <utility>
OutputWriter::OutputWriter(std::string fileName, ParticleContainer &container) : fileName{std::move(fileName)},
                                                                                       container{container} {

}
