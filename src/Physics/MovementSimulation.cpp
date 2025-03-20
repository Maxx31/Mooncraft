#include "MovementSimulation.h"

#include "../Math/AABB.h"
#include "../Math/Ray.h"

bool MovementSimulation::canMove(const glm::vec3& from, const glm::vec3& to, World& world) 
{
  AABB playerBox(AABB::PlayerBoxOffsets);
  glm::vec3 movementDirection = from - to;

  for (auto& point: playerBox.points) 
  {
    point += to;
  }

  for (const auto& point: playerBox.points) {
    // Determine if any block intersect with player
    if (Ray ray{point, movementDirection, world, 3.0f}) 
    {
      glm::vec3 position = ray.getHitTarget().position;

      if (AABB::fromBlockPosition(position).intersect(playerBox)) {
        return false;
      }
    }
  }

  return true;
}