#pragma once

#include <utility>

#include "../MCraft.h"
#include "../Core/Persistence.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture.h"
#include "../Renderer/VertexArray.h"
#include "../Core/World.h"
#include "BlockOutline.h"
#include "Crosshair.h"
#include "Player.h"
#include "Skybox.h"

class Scene {
public:
  explicit Scene(const std::string& savePath);

  void update(float deltaTime);

  void render();
  void renderGui();

  void onResized(int32_t width, int32_t height);
  void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
  void onCursorPositionEvent(double x, double y);
  void onMouseButtonEvent(int32_t button, int32_t action, int32_t mods);

private:
  SharedRef<Persistence> persistence;
  SharedRef<World> world;

  Skybox skybox;

  Player player;
  glm::mat4 projectionMatrix = glm::mat4(1);

  Crosshair crosshair;
  BlockOutline outline;
  bool isMenuOpen = false;

  void toggleMenu();
  void updateMouse();
};