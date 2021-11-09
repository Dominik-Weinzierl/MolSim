#pragma once

#include <arguments/argument/XMLArgument/XMLArgument.h>
#include "template/input.h"
#include <memory>

class XMLReader {
 public:
  explicit XMLReader(const std::string &path);

  [[nodiscard]] std::unique_ptr<XMLArgument> readXML() const;
 private:
  std::unique_ptr<simulation_t> simulation;
};

