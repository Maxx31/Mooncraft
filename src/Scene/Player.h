#pragma once

#include "../MCraft.h"
#include "../Physics/MovementSimulation.h"
#include "../Core/World.h"
#include "Camera.h"

class Player {
public:
  static constexpr float reach = 4.5f;

  explicit Player(const SharedRef<World>& world, const SharedRef<Persistence>& persistence);

  void update(float deltaTime);

  [[nodiscard]] bool getIsSurvivalMovement() const { return isSurvivalMovement; };
  void setSurvivalMovement(bool isSurvival) 
  {
    gravity = glm::vec3(0);
    isSurvivalMovement = isSurvival;
  };

  [[nodiscard]] const Camera& getCamera() const { return camera; };

  void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
  void onMouseButtonEvent(int32_t button, int32_t action, int32_t mods);
  void onCursorPositionEvent(double d, double d1);

  [[nodiscard]] BlockData::BlockType getBlockToPlace() const { return blockToPlace; };
  void setBlockToPlace(BlockData::BlockType block) { blockToPlace = block; };

  void resetMousePosition();

  ~Player();

private:
  static constexpr float GravityConstant = 46.62f;

  Camera camera;

  SharedRef<World> world;
  SharedRef<Persistence> persistence;
  BlockData::BlockType blockToPlace = BlockData::BlockType::grass;

  glm::vec3 gravity{0};
  glm::vec3 velocity{0};

  float walkingSpeed = 5;
  float runningSpeed = 8;
  float mouseSensitivity = .5;
  bool canJump = false;
  bool isRunning = false;
  bool isSurvivalMovement = false;
  bool resetMouse = true;
};