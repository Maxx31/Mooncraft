#pragma once

#include "../MCraft.h"

class Util 
{
  Util() = default;

public:
  class HashVec2 
  {
  public:
    size_t operator()(const glm::ivec2& coord) const noexcept {
      return std::hash<int32_t>{}(coord.x) | (std::hash<int32_t>{}(coord.y) << sizeof(int32_t) * 8); //Add X and Y coordinates inside custom Hash Function
    };
  };

  static SharedRef<std::string> readBinaryFile(const std::string& path);
  static int32_t positiveMod(int32_t num, int32_t divisor);
};