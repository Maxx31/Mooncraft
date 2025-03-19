#pragma once

#include "../Scene/Camera.h"
#include "../Util/Util.h"
#include "../World/Chunk.h"
#include "../MCraft.h"

class Persistence 
{
  std::string path;
  Camera camera;
  std::unordered_map<glm::ivec2, SharedRef<Chunk>, Util::HashVec2> chunks;

public:
  explicit Persistence(std::string path);

  void commitChunk(const SharedRef<Chunk>& chunk) { chunks[chunk->getPosition()] = chunk; }

  [[nodiscard]] SharedRef<Chunk> getChunk(glm::ivec2 position) const 
  {
    if (!chunks.contains(position)) {
      return nullptr;
    }
    return chunks.at(position);
  };

  void commitCamera(const Camera& newCamera) { camera = newCamera; }
  [[nodiscard]] const Camera& getCamera() const { return camera; };

  ~Persistence();
};