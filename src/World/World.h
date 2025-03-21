#pragma once

#include "../AssetManager/AssetManager.h"
#include "../MCraft.h"
#include "../Persistence/Persistence.h"
#include "../Rendering/ShaderProgram.h"
#include "../Rendering/Texture.h"
#include "Chunk.h"
#include "WorldGenerator.h"

class World {
public:
  explicit World(const SharedRef<Persistence>& persistence, int32_t seed = 1337);

  SharedRef<Chunk> getChunk(glm::ivec2 position);
  void addChunk(glm::ivec2 position, const SharedRef<Chunk>& chunk);
  [[nodiscard]] static glm::ivec2 getChunkIndex(glm::ivec3 position);

  [[nodiscard]] BlockData getBlockAt(glm::ivec3 position);
  [[nodiscard]] std::optional<BlockData> getBlockAtIfLoaded(glm::ivec3 position) const;
  [[nodiscard]] bool isChunkLoaded(glm::ivec2 position) const;
  bool placeBlock(BlockData block, glm::ivec3 position);

  void update(const glm::vec3& playerPosition, float deltaTime);
  void render(glm::vec3 playerPos, glm::mat4 transform, float rotation);

  static bool isValidBlockPosition(glm::ivec3 position);
  void setTextureAtlas(const SharedRef<const Texture>& texture);

private:
  std::unordered_map<glm::ivec2, SharedRef<Chunk>, Util::HashVec2> chunks;
  SharedRef<const Texture> textureAtlas;
  SharedRef<const ShaderProgram> shader;
  SharedRef<Persistence> persistence;
  WorldGenerator generator;

  int32_t viewDistance = 10;
  float textureAnimation = 0;
  static constexpr float TextureAnimationSpeed = 2;

  SharedRef<Chunk> generateOrLoadChunk(glm::ivec2 position);
};