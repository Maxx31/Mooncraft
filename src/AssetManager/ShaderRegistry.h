#pragma once
#include "../Rendering/Shader.h"
#include "AssetRegistry.h"

class ShaderRegistry : public AssetRegistry<Shader> {
  SharedRef<const Shader> loadAsset(const std::string &name) override { return std::make_shared<Shader>(name); }
};