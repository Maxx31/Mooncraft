#pragma once
#include <utility>

#include "../MCraft.h"
#include "Camera.h"
#include "Chunk.h"
#include "Entity.h"

#include "../Rendering/ShaderProgram.h"
#include "../Rendering/Texture.h"
#include "../Rendering/VertexArray.h"

class Scene 
{
  std::vector<Entity> entities;
  bool initialized = false;

  SharedRef<Chunk> chunk;
  SharedRef<const Texture> textureAtlas;
  SharedRef<const ShaderProgram> defaultShader;

  Camera camera;
  glm::mat4 projectionMatrix;

public:

  Scene();
  explicit Scene(std::vector<Entity> entities);

  void addEntity(Entity &&entity) { entities.emplace_back(entity); };
  void addEntity(const Entity &entity) { entities.emplace_back(entity); };

  void init();
  void update(float deltaTime);
  void render();
  void renderGui();

  void onResized(int32_t width, int32_t height);
};
