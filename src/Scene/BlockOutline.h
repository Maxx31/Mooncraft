#pragma once

#include "../Rendering/ShaderProgram.h"
#include "../Rendering/VertexArray.h"
#include "../MCraft.h"

class BlockOutline 
{
public:
  BlockOutline();

  void render(const glm::mat4& transform);

private:
  SharedRef<const ShaderProgram> outlinedBlockShader;
  SharedRef<VertexArray> outlinedBlockVertexArray;
};