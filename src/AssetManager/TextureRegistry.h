#pragma once

#include "../Renderer/Texture.h"
#include "AssetRegistry.h"

class TextureRegistry : public AssetRegistry<Texture> 
{
  SharedRef<const Texture> loadAsset(const std::string& name) override { return Texture::loadTexture2D(name); }
};