#pragma once

#include "../Rendering/Texture.h"
#include "AssetRegistry.h"

class TextureArrayRegistry : public AssetRegistry<Texture> 
{
  SharedRef<const Texture> loadAsset(const std::string& name) override { return Texture::loadTexture2DArray(name); }
};