#pragma once

#include "../World/World.h"
#include "../MCraft.h"

struct HitTarget 
{
  glm::vec3 position;
  BlockData block;
  glm::vec3 neighbor;
  bool hasNeighbor = false;
};

class Ray 
{
public:
  Ray(glm::vec3 position, glm::vec3 direction, World& world, float reach);

  [[nodiscard]] bool hasHit() const { return successful; };
  [[nodiscard]] HitTarget getHitTarget() const { return hitTarget; };
  explicit operator bool() const { return hasHit(); }

private:
	bool successful;
    HitTarget hitTarget;
};