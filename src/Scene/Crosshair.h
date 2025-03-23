#pragma once

#include "../MCraft.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/VertexArray.h"

class Crosshair {
public:
  Crosshair();

  void update(float aspectRatio);
  void render();

private:
  glm::mat4 transform;
  VertexArray vertexArray;
  SharedRef<const ShaderProgram> shader;
};