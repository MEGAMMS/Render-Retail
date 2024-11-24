#pragma once

#include "core.h"

struct Image{
  uint32_t width, height;
  std::vector<uint8_t> data;
};