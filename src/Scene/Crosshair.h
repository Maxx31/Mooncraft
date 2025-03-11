#pragma once

#include "../Rendering/ShaderProgram.h"
#include "../Rendering/VertexArray.h"
#include "../MCraft.h"

class Crosshair 
{
  glm::mat4 transform;
  VertexArray vertexArray;
  SharedRef<const ShaderProgram> shader;

public:
  Crosshair();

  void update(float aspectRatio);
  void render();
};