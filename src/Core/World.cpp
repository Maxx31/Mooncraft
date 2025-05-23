#include "World.h"

#include "../Util/Util.h"

World::World(const SharedRef<Persistence>& persistence, int32_t seed) : persistence(persistence), generator(seed)
{
  shader = AssetManager::instance().loadShaderProgram("assets/shaders/default");
  setTextureAtlas(AssetManager::instance().loadTextureArray("assets/textures/default_texture.png"));
}

SharedRef<Chunk> World::generateOrLoadChunk(glm::ivec2 position) 
{
  SharedRef<Chunk> chunk = persistence->getChunk(position);

  if (chunk != nullptr) {
    return chunk;
  }

  chunk = std::make_shared<Chunk>(position); //Bottleneck

  generator.populateChunk(chunk);
  persistence->commitChunk(chunk);
  return chunk;
}

void World::update(const glm::vec3& playerPosition, float deltaTime) 
{
  currentTime += deltaTime;
  glm::vec2 playerChunkPosition = getChunkIndex(playerPosition);

  auto chunksCopy = chunks;
  float unloadDistance = static_cast<float>(viewDistance + 1) * 16 + 8.0f;
  for (const auto& [chunkPosition, chunk]: chunksCopy) 
  {
    if (glm::abs(glm::distance(glm::vec2(chunkPosition), playerChunkPosition)) > unloadDistance) {
      chunks.erase(chunkPosition);
    }
  }

  float loadDistance = static_cast<float>(viewDistance) * 16 + 8.0f;
  for (int32_t i = -viewDistance; i < viewDistance; i++) {
    for (int32_t j = -viewDistance; j < viewDistance; j++) {
      glm::ivec2 position = glm::ivec2(i * 16, j * 16) + glm::ivec2(playerChunkPosition);
      if (isChunkLoaded(position)) {
        continue;
      }

      float distance = glm::abs(glm::distance(glm::vec2(position), playerChunkPosition));
      if (distance <= loadDistance) 
      {
          //addChunkAsync(position);
          addChunk(position, generateOrLoadChunk(position));
      }
    }
  }
}

void World::render(glm::vec3 playerPos, glm::mat4 transform) 
{
  static auto sortedChunkIndices = std::make_shared<std::vector<std::pair<glm::vec2, float>>>();
  sortedChunkIndices->clear();
  if (sortedChunkIndices->capacity() < chunks.size()) {
    sortedChunkIndices->reserve(chunks.size());
  }

  std::array<glm::ivec2, 4> chunkCoordinateOffsets = {{{0, 16}, {16, 0}, {16, 16}}};

  glm::vec2 playerChunk = glm::vec2(playerPos.x, playerPos.z);
  for (const auto& [key, value]: chunks) {
    float maxDistance = glm::distance(playerChunk, glm::vec2(key));

    for (const auto& offset: chunkCoordinateOffsets) {
      float distance = glm::distance(playerChunk, glm::vec2(key + offset));

      if (distance > maxDistance) {
        maxDistance = distance;
      }
    }

    sortedChunkIndices->push_back({key, maxDistance});
  }

  std::sort(sortedChunkIndices->begin(), sortedChunkIndices->end(),
            [](const auto& a, const auto& b) { return b.second < a.second; });


const int32_t animationProgress = static_cast<int32_t>(currentTime) % 5;

  // animation offsets for water and lava
  const static int32_t animationOffsets[] = {0, 1, 2, 17, 18};

  const int32_t animationOffset = animationOffsets[animationProgress];

    shader->setUInt("textureAnimation", animationOffset);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (const auto& index: *sortedChunkIndices) 
  {
    chunks[index.first]->setUseAmbientOcclusion(useAmbientOcclusion);
    chunks[index.first]->render(transform, *this);
  }

  glDisable(GL_BLEND);
}

const BlockData* World::getBlockAt(glm::ivec3 position) 
{
  return getChunk(getChunkIndex(position))->getBlockAt(Chunk::toChunkCoordinates(position));
}

bool World::isValidBlockPosition(glm::ivec3 position) 
{
  return Chunk::isValidPosition(position);
}

bool World::placeBlock(BlockData block, glm::ivec3 position) 
{
  if (!Chunk::isValidPosition(position)) {
    return false;
  }

  glm::ivec3 positionInChunk = Chunk::toChunkCoordinates(position);
  getChunk(getChunkIndex(position))->placeBlock(block, positionInChunk);

  const std::array<glm::ivec3, 4> blocksAround = {{{0, 0, 1}, {1, 0, 0}, {0, 0, -1}, {-1, 0, 0}}};
  for (const glm::ivec3& offset: blocksAround) {
    glm::ivec3 neighbor = offset + positionInChunk;
    if (!Chunk::isInBounds(neighbor.x, neighbor.y, neighbor.z)) {
      getChunk(getChunkIndex(position + offset))->setDirty();
    }
  }

  return true;
}
glm::ivec2 World::getChunkIndex(glm::ivec3 position) 
{
  return {position.x - Util::positiveMod(position.x, Chunk::HorizontalSize),
          position.z - Util::positiveMod(position.z, Chunk::HorizontalSize)};
}


SharedRef<Chunk> World::getChunk(glm::ivec2 position) 
{
  if (!isChunkLoaded(position)) 
  {
    addChunk(position, generateOrLoadChunk(position));
  }

  return chunks.at(position);
}

void World::addChunk(glm::ivec2 position, const SharedRef<Chunk>& chunk) 
{
  chunks[position] = chunk;
  std::array<glm::ivec2, 4> chunksAround = {{{0, 16}, {16, 0}, {0, -16}, {-16, 0}}};
  for (const glm::ivec2& offset: chunksAround) {
    glm::ivec2 neighborPosition = position + offset;

    if (!isChunkLoaded(neighborPosition))
      continue;

    chunks[neighborPosition]->setDirty();
  }
}
//
//void World::addChunkAsync(glm::ivec2 position) 
//{
//    threadPool.EnqueueJob(std::bind(&World::addChunkWorker, this, position));
//}
//
//void World::addChunkWorker(glm::ivec2 position)
//{
//    SharedRef<Chunk> chunk = generateOrLoadChunk(position);
//
//    std::scoped_lock lock(chunkMutex); //Protects data
//
//    chunks[position] = chunk;
//    //std::array<glm::ivec2, 4> chunksAround = {{{0, 16}, {16, 0}, {0, -16}, {-16, 0}}};
//    //for (const glm::ivec2 &offset: chunksAround)
//    //{
//    //    glm::ivec2 neighborPosition = position + offset;
//
//    //    if (!isChunkLoaded(neighborPosition))
//    //        continue;
//
//    //    chunks[neighborPosition]->setDirty();
//    //}
//}

void World::setTextureAtlas(const SharedRef<const Texture>& texture) {
  textureAtlas = texture;
  shader->setTexture("atlas", textureAtlas, 0);
}

const BlockData* World::getBlockAtIfLoaded(glm::ivec3 position) const {
  glm::ivec2 index = getChunkIndex(position);
  if (!isChunkLoaded(index)) {
    return nullptr;
  }

  return chunks.at(index)->getBlockAt(Chunk::toChunkCoordinates(position));
}

bool World::isChunkLoaded(glm::ivec2 position) const {
  return chunks.contains(position);
}