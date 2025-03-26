#pragma once

#include "../MCraft.h"

#include "Chunk.h"
#include "ThreadPool.h"

class WorldGenerator {
public:
  WorldGenerator(int32_t seed);
  [[nodiscard]] int32_t getSeed() const { return seed; };

  void populateChunk(const SharedRef<Chunk>& chunkRef);

private:
  void populateChunkMultithreaded(const SharedRef<Chunk> &chunkRef);

  ThreadPool threadPool;

  int32_t seed;
  FastNoiseLite noise;
};