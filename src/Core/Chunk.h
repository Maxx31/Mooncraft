#pragma once

#include "../Renderer/BlockMesh.h"
#include "../Renderer/BlockVertex.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/VertexArray.h"
#include "../MCraft.h"
#include "BlockData.h"

class Persistence;
class World;

class Chunk 
{
public:
  explicit Chunk(const glm::ivec2& worldPosition);
  void render(const glm::mat4& transform, const World& world);

  void setDirty() { renderState = RenderState::dirty; };
  void setUseAmbientOcclusion(bool enabled) {
    if (enabled == useAmbientOcclusion) {
      return;
    }

    setDirty();
    useAmbientOcclusion = enabled;
  };

  void placeBlock(BlockData block, const glm::ivec3& position) {
    placeBlock(block, position.x, position.y, position.z);
  }

  void placeBlock(BlockData block, int32_t x, int32_t y, int32_t z) {
    assert(isInBounds(x, y, z));

    renderState = RenderState::dirty;
    data[x][y][z] = block;
  }

  [[nodiscard]] const BlockData* getBlockAt(const glm::ivec3& position) const {
    return &data[position.x][position.y][position.z];
  }

  static bool isInBounds(int32_t x, int32_t y, int32_t z) {
    return x >= 0 && x < HorizontalSize && y >= 0 && y < VerticalSize && z >= 0 && z < HorizontalSize;
  }

  [[nodiscard]] const BlockData* getBlockAtOptimized(const glm::ivec3& pos, const World& world) const;
  static bool isValidPosition(glm::ivec3 position) { return position.y >= 0 && position.y < VerticalSize; }
  static glm::ivec3 toChunkCoordinates(const glm::ivec3& globalPosition);

  glm::ivec2 getPosition() { return worldPosition; }
  friend Persistence;

public:
  static constexpr int32_t HorizontalSize = 16;
  static constexpr int32_t VerticalSize = 256;

  static constexpr int32_t BlockCount = HorizontalSize * HorizontalSize * VerticalSize;
  static constexpr int32_t MaxVertexCount = BlockCount * 8;


private:
  enum class RenderState {
      initial,
      ready,
      dirty
  };
  int32_t solidVertexCount;
  int32_t semiTransparentVertexCount;
  SharedRef<VertexArray> mesh;
  SharedRef<const ShaderProgram> shader;

  bool useAmbientOcclusion = true;

  RenderState renderState;
  glm::ivec2 worldPosition;

  BlockData data[HorizontalSize][VerticalSize][HorizontalSize];

  void createMesh(const World &world);
  void init();
};