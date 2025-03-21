#pragma once

#include "../MCraft.h"
#include "../Rendering/ShaderProgram.h"
#include "../Rendering/VertexArray.h"

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