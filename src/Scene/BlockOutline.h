#pragma once

#include "../Rendering/ShaderProgram.h"
#include "../Rendering/VertexArray.h"
#include "../MCraft.h"

class BlockOutline 
{
  SharedRef<const ShaderProgram> outlinedBlockShader;
  SharedRef<VertexArray> outlinedBlockVertexArray;

public:
  BlockOutline();

  void render(const glm::mat4& transform);
};