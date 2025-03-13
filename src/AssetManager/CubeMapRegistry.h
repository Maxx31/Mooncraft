#pragma once

#include "AssetRegistry.h"

class CubeMapRegistry : public AssetRegistry<Texture>
{
  SharedRef<const Texture> loadAsset(const std::string& name) override { return Texture::loadCubeMapTexture(name); };
};