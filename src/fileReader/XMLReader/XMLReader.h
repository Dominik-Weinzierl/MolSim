#pragma once
#include "template/input.h"

class XMLReader {
 public:
  explicit XMLReader(const std::string& path);

 private:
  std::unique_ptr<simulation_t> simulation;
};

