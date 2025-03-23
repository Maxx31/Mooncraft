#pragma once

#include "../Core/World.h"
#include "../MCraft.h"

namespace MovementSimulation 
{
  bool canMove(const glm::vec3 &from, const glm::vec3 &to, World &world);
};