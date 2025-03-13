#pragma once

#include "../AssetManager/AssetManager.h"
#include "../Rendering/ShaderProgram.h"
#include "../Rendering/Texture.h"
#include "../MCraft.h"
#include "Chunk.h"
#include "WorldGenerator.h"

class HashVec2 
{
public:
  size_t operator()(const glm::ivec2& coord) const noexcept {
    return std::hash<int32_t>{}(coord.x) | (std::hash<int32_t>{}(coord.y) << sizeof(int32_t) * 8);
  };
};

class World 
{
  std::unordered_map<glm::ivec2, SharedRef<Chunk>, HashVec2> chunks;
  SharedRef<const Texture> textureAtlas;
  SharedRef<const ShaderProgram> defaultShader;
  WorldGenerator generator;

  int32_t viewDistance = 5;

  SharedRef<Chunk> generateOrLoadChunk(glm::ivec2 position);

public:
  World(int32_t seed = 1337);

  SharedRef<Chunk> getChunk(glm::ivec2 position);
  void addChunk(glm::ivec2 position, const SharedRef<Chunk>& chunk) { chunks[position] = chunk; };
  [[nodiscard]] static glm::ivec2 getChunkIndex(glm::ivec3 position);

  [[nodiscard]] BlockData getBlockAt(glm::ivec3 position);
  bool placeBlock(BlockData block, glm::ivec3 position);

  void update(const glm::vec3& playerPosition);
  void render(glm::vec3 playerPos, glm::mat4 transform);

  static bool isValidBlockPosition(glm::ivec3 position);
};