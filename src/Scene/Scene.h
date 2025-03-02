#pragma once
#include <utility>

#include "../MCraft.h"
//#include "Camera.h"
#include "Entity.h"

#include "../Rendering/ShaderProgram.h"
#include "../Rendering/VertexArray.h"

class Scene {
  std::vector<Entity> entities;
  bool initialized = false;

  SharedRef<VertexArray> vao;
  SharedRef<const ShaderProgram> defaultShader;

public:
  Scene() = default;
  explicit Scene(std::vector<Entity> entities) : entities(std::move(entities)) {}

  void addEntity(Entity &&entity) { entities.emplace_back(entity); };
  void addEntity(const Entity &entity) { entities.emplace_back(entity); };

  void init();
  void update(float deltaTime);
  void render();
  void renderGui();
};
