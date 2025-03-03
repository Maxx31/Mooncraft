#pragma once

#include "../Rendering/Texture.h"
#include "AssetRegistry.h"


class TextureRegistry : public AssetRegistry<Texture> 
{
  SharedRef<const Texture> loadAsset(const std::string& name) override 
  {
    uint32_t width, height;
    std::vector<uint8_t> image;
    uint32_t error = lodepng::decode(image, width, height, name, LCT_RGBA);

    if (error != 0) 
    {
      std::cerr << "Failed to decode texture with error:" << lodepng_error_text(error) << std::endl;
      return nullptr;
    }

    SharedRef<Texture> texture = Texture::createRef();
    texture->bufferRGBAData(width, height, image);
    return texture;
  }
};