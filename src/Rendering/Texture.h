#pragma once

#include "../MCraft.h"
#include "Image.h"

class Texture
{
  uint32_t id = 0;
  uint32_t type;

public:
  Texture(const Texture&) = delete;
  Texture(Texture&) = delete;
  Texture(Texture&&) = delete;

  Texture(uint32_t type);

  [[nodiscard]] bool isValid() const { return id != 0; };

  void bind() const;
  void bindToSlot(uint32_t slot) const;
  void unbind() const;

  void buffer2DRGBAData(const Image& image);
  void bufferCubeMapRGBAData(const std::array<SharedRef<const Image>, 6>& images);

  ~Texture();

  static SharedRef<const Texture> loadTexture2D(const std::string& name);
  static SharedRef<const Texture> loadCubeMapTexture(const std::string& name);
};