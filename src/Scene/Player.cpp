#include "Player.h"

const glm::mat4& Player::updateView() 
{
  return view = calcView();
}


const glm::mat4& Player::lookAt(glm::vec3 eye, glm::vec3 center)
{
  position = eye;
  updatePlayerDirection(center);
  return updateView();
}

const glm::mat4& Player::setPosition(glm::vec3 eye)
{
  position = eye;
  return updateView();
}

void Player::update(float deltaTime) 
{
  auto moveDirection = glm::vec3(0);

  for (const auto& [isMoving, direction]: directions)
  {
    if (!isMoving) continue;
    moveDirection += direction;
  }

  if (glm::length(moveDirection) > 0) 
  {
    position += glm::normalize(moveDirection) * movementSpeed * deltaTime;
    updateView();
  }
}

void Player::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) 
{
  if (action == 2) return;  // don't respond to repeatedly pressed buttons

  if (key == 87 || key == 265) {
    directions[0].isMoving = action == 1;
  } else if (key == 83 || key == 264) {
    directions[1].isMoving = action == 1;
  } else if (key == 65 || key == 263) {
    directions[2].isMoving = action == 1;
  } else if (key == 68 || key == 262) {
    directions[3].isMoving = action == 1;
  } else if (key == 32) {
    directions[4].isMoving = action == 1;
  } else if (key == 340) {
    directions[5].isMoving = action == 1;
  }
}

void Player::onMouseButtonEvent(int32_t button, int32_t action, int32_t mods) 
{
}

void Player::onCursorPositionEvent(double x, double y)
{
  static double lastX = x;
  static double lastY = y;

  yaw += static_cast<float>(-lastX + x) * mouseSensitivity;
  pitch = glm::clamp(pitch + static_cast<float>(lastY - y) * mouseSensitivity, -89.0f, 89.0f);

  lastX = x;
  lastY = y;
  updatePlayerOrientation();
}

void Player::updatePlayerDirection(glm::vec3 newForward) 
{
  lookDirection = newForward;
  newForward.y = 0;
  forward = glm::normalize(newForward);
  backward = -newForward;

  right = glm::normalize(glm::cross(newForward, up));
  left = -right;
}

void Player::updatePlayerOrientation() 
{
  updatePlayerDirection(glm::normalize(glm::vec3{
     glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
     glm::sin(glm::radians(pitch)),
     glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
  }));

  updateView();
}

glm::mat4 Player::calcView() 
{
  return glm::lookAt(position, position + lookDirection, up);
}