#pragma once

#include "../MCraft.h"
#include "Chunk.h"

class WorldGenerator 
{
  int32_t seed;
  FastNoiseLite noise;

public:
  WorldGenerator(int32_t seed);
  [[nodiscard]] int32_t getSeed() const { return seed; };

  void populateChunk(const SharedRef<Chunk>& chunkRef);
};