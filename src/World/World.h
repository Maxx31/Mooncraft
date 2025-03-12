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
    return std::hash<int>{}(coord.x) | (std::hash<int>{}(coord.y) << sizeof(int) * 8); //First 32 bit for coord X, and second 32 bits for coord y
  };
};

class World 
{
  std::unordered_map<glm::ivec2, SharedRef<Chunk>, HashVec2> chunks;
  SharedRef<const Texture> textureAtlas;
  SharedRef<const ShaderProgram> defaultShader;

  WorldGenerator generator;

  SharedRef<Chunk> generateOrLoadChunk(glm::ivec2 position) 
  {
    SharedRef<Chunk> chunk = std::make_shared<Chunk>(position);
    generator.populateChunk(chunk);

    return chunk;
  }

public:
  World(int seed = 228);

  SharedRef<Chunk> getChunk(glm::ivec2 position);
  void addChunk(glm::ivec2 position, const SharedRef<Chunk>& chunk) { chunks[position] = chunk; };
  [[nodiscard]] static glm::ivec2 getChunkIndex(glm::ivec3 position);

  [[nodiscard]] BlockData getBlockAt(glm::ivec3 position);
  bool placeBlock(BlockData block, glm::ivec3 position);

   void render(glm::vec3 playerPos, glm::mat4 transform);
  int GetChunksAmmount() { return chunks.size(); }

   static bool isValidBlockPosition(glm::ivec3 position);
};