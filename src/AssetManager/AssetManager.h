#pragma once
#include "../Rendering/ShaderProgram.h"
#include "../MCraft.h"
#include "AssetRegistry.h"
#include "ShaderProgramRegistry.h"
#include "TextRegistry.h"
#include "../Rendering/Shader.h"
#include "ShaderRegistry.h"

class AssetManager {

  TextRegistry textRegistry;
  ShaderRegistry shaderRegistry;
  ShaderProgramRegistry shaderProgramRegistry;

  AssetManager() = default;

public:
  AssetManager(const AssetManager &) = delete;
  AssetManager(AssetManager &) = delete;
  AssetManager(AssetManager &&) = delete;

  static AssetManager &instance() {
    static AssetManager manager;
    return manager;
  };
  SharedRef<const std::string> loadText(const std::string &name) { return textRegistry.get(name); };

  SharedRef<const Shader> loadShader(const std::string &name) { return shaderRegistry.get(name); };
  SharedRef<const ShaderProgram> loadShaderProgram(const std::string &name) { return shaderProgramRegistry.get(name); };
};
