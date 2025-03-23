#pragma once

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/VertexArray.h"
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