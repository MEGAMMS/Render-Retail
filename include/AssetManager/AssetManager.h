#pragma once

#include "Render/Shader.h"
#include "Render/ShaderProgram.h"
#include "core.h"
#include "AssetManager/AssetRegistry.h"
#include "AssetManager/ShaderProgramRegistry.h"
#include "AssetManager/ShaderRegistry.h"
#include "AssetManager/TextRegistry.h"
#include "AssetManager/ImageRegistry.h"
#include "AssetManager/TextureRegistry.h"

class AssetManager {
  TextRegistry textRegistry;
  ImageRegistry imageRegistry;
  TextureRegistry textureRegistry;
  // CubeMapRegistry cubeMapRegistry;
  ShaderRegistry shaderRegistry;
  ShaderProgramRegistry shaderProgramRegistry;

  AssetManager() = default;

public:
  AssetManager(const AssetManager&) = delete;
  AssetManager(AssetManager&) = delete;
  AssetManager(AssetManager&&) = delete;

  static AssetManager& instance() {
    static AssetManager manager;
    return manager;
  };

  void removeTextFromRegistry(const std::string& name) { textRegistry.remove(name); }
  void removeImageFromRegistry(const std::string& name) { imageRegistry.remove(name); }
  void removeTextureFromRegistry(const std::string& name) { textureRegistry.remove(name); }
  // void removeCubeMapFromRegistry(const std::string &name) { cubeMapRegistry.remove(name); };
  void removeShaderFromRegistry(const std::string& name) { shaderRegistry.remove(name); }
  void removeShaderProgramFromRegistry(const std::string& name) { shaderProgramRegistry.remove(name); }

  std::shared_ptr<const std::string> loadText(const std::string& name) { return textRegistry.get(name); };
  std::shared_ptr<const Image> loadImage(const std::string& name) { return imageRegistry.get(name); };
  std::shared_ptr<const Texture> loadTexture(const std::string& name = "assets/default-texture.png") { return textureRegistry.get(name); };

  /// the expected input format: right;left;top;bottom;front;back
  // std::shared_ptr<const Texture> loadCubeMap(const std::string &name) { return cubeMapRegistry.get(name); };
  std::shared_ptr<const Shader> loadShader(const std::string& name) { return shaderRegistry.get(name); };
  std::shared_ptr<const ShaderProgram> loadShaderProgram(const std::string& name) { return shaderProgramRegistry.get(name); };
};
