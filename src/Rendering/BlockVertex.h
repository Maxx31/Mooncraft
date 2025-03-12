#pragma once

#include "../World/BlockData.h"
#include "../MCraft.h"
#include "VertexArray.h"

struct BlockVertex
{
  glm::vec3 position;
  glm::vec2 uvCoords;

  void offset(int32_t x, int32_t y, int32_t z) { position += glm::vec3(x, y, z); }

  void setType(int32_t offsetX, int32_t offsetY, int32_t offsetZ, BlockData::BlockType type);

  static std::vector<VertexAttribute> vertexAttributes() 
  {
    return {VertexAttribute(3, VertexAttribute::Float, 0),
            VertexAttribute(2, VertexAttribute::Float, sizeof(glm::vec3))};
  }
};
