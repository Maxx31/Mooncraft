#pragma once

#include "../Rendering/ShaderProgram.h"
#include "../Rendering/VertexArray.h"
#include "../MCraft.h"

class Skybox {
  glm::mat4 transform{1};
  VertexArray vertexArray{
     std::vector<glm::vec3>{
        {1, 1, 1},
        {1, 1, -1},
        {1, -1, 1},
        {1, -1, -1},
        {-1, 1, 1},
        {-1, 1, -1},
        {-1, -1, 1},
        {-1, -1, -1},
     },
     std::vector<VertexAttribute>{{3, VertexAttribute::Float, 0}},
     std::vector<uint8_t>{0, 1, 5, 4, 0, 5, 2, 1, 0, 1, 2, 3, 7, 4, 5, 4, 7, 6,
                          1, 3, 7, 1, 7, 5, 4, 6, 0, 2, 0, 6, 3, 2, 6, 7, 3, 6},
  };
  SharedRef<const ShaderProgram> shader;

public:
  Skybox();
  void update(const glm::mat4& projection, const glm::mat4& cameraView);
  void render();
};