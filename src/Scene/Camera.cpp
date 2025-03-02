#include "Camera.h"

Camera::Camera() : position(), direction(), up({0, 1, 0}), viewMatrix(calcView()) {};

const glm::mat4& Camera::lookAt(glm::vec3 eye, glm::vec3 center) 
{
  position = eye;
  direction = center;
  return viewMatrix = calcView();
}
const glm::mat4& Camera::setPosition(glm::vec3 eye) 
{
  position = eye;
  return viewMatrix = calcView();
}