#pragma once

#include "AssetRegistry.h"

class ShaderProgramRegistry : public AssetRegistry<ShaderProgram> {
  std::shared_ptr<const ShaderProgram> loadAsset(const std::string& name) override { return std::make_shared<ShaderProgram>(name); }
};