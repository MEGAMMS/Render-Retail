#pragma once

#include "Render/Shader.h"
#include "AssetRegistry.h"

class ShaderRegistry : public AssetRegistry<Shader> {
  std::shared_ptr<const Shader> loadAsset(const std::string &name) override { return std::make_shared<Shader>(name); }
};