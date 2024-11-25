#pragma once

#include "Render/Texture.h"
#include "AssetRegistry.h"


class TextureRegistry : public AssetRegistry<Texture> {
  std::shared_ptr<const Texture> loadAsset(const std::string& name) override {
    return Texture::loadTexture2D(name);
  }
};