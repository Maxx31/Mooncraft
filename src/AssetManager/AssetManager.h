#pragma once
#include "../Rendering/Shader.h"
#include "../Rendering/ShaderProgram.h"
#include "../MCraft.h"
#include "AssetRegistry.h"

#include "ShaderProgramRegistry.h"
#include "ShaderRegistry.h"

#include "TextRegistry.h"
#include "TextureRegistry.h"

class AssetManager {

  TextRegistry textRegistry;
  TextureRegistry textureRegistry;

  ShaderRegistry shaderRegistry;
  ShaderProgramRegistry shaderProgramRegistry;

  AssetManager() = default;

public:
  AssetManager(const AssetManager &) = delete;
  AssetManager(AssetManager &) = delete;
  AssetManager(AssetManager &&) = delete;

  static AssetManager &instance() 
  {
    static AssetManager manager;
    return manager;
  };
  
  void removeTextFromRegistry(const std::string &name) { textRegistry.remove(name); }
  void removeTextureFromRegistry(const std::string &name) { textureRegistry.remove(name); }
  void removeShaderFromRegistry(const std::string &name) { shaderRegistry.remove(name); }
  void removeShaderProgramFromRegistry(const std::string &name) { shaderProgramRegistry.remove(name); }

  SharedRef<const std::string> loadText(const std::string &name) { return textRegistry.get(name); };
  SharedRef<const Texture> loadTexture(const std::string &name) { return textureRegistry.get(name); };
  SharedRef<const Shader> loadShader(const std::string &name) { return shaderRegistry.get(name); };
  SharedRef<const ShaderProgram> loadShaderProgram(const std::string &name) { return shaderProgramRegistry.get(name); };
};
