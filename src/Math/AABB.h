#pragma once

#include "../MCraft.h"

struct AABB 
{
  // Determine the size of player in each direction
  static constexpr std::array<glm::vec3, 8> PlayerBoxOffsets = {{
     {0.3, 0.3, 0.3},
     {0.3, 0.3, -0.3},
     {-0.3, 0.3, 0.3},
     {-0.3, 0.3, -0.3},
     {0.3, -1.5, 0.3},
     {0.3, -1.5, -0.3},
     {-0.3, -1.5, 0.3},
     {-0.3, -1.5, -0.3},
  }};
  std::array<glm::vec3, 8> points;

  explicit AABB(const std::array<glm::vec3, 8>& points) : points(points) {}

  static AABB fromBlockPosition(const glm::vec3& position) 
  {
    return AABB({
       position,
       position + glm::vec3{1, 1, 1},
       position + glm::vec3{1, 1, 0},
       position + glm::vec3{1, 0, 1},
       position + glm::vec3{1, 0, 0},
       position + glm::vec3{0, 1, 1},
       position + glm::vec3{0, 1, 0},
       position + glm::vec3{0, 0, 1},
    });
  }

  [[nodiscard]] bool intersect(const AABB& aabb) const;

  [[nodiscard]] float getMinAt(int32_t index) const;
  [[nodiscard]] float getMaxAt(int32_t index) const;

  [[nodiscard]] float getMinX() const { return getMinAt(0); };
  [[nodiscard]] float getMinY() const { return getMinAt(1); };
  [[nodiscard]] float getMinZ() const { return getMinAt(2); };
  [[nodiscard]] float getMaxX() const { return getMaxAt(0); };
  [[nodiscard]] float getMaxY() const { return getMaxAt(1); };
  [[nodiscard]] float getMaxZ() const { return getMaxAt(2); };
};