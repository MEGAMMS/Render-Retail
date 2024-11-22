#pragma once

#include "Render/ShaderProgram.h"
#include "core.h"

template<typename T>
class AssetRegistry {
  std::unordered_map<std::string, std::weak_ptr<const T>> registry;
  virtual std::shared_ptr<const T> loadAsset(const std::string& name) = 0;

  [[nodiscard]] bool hasAsset(const std::string& name) const {
    if (!registry.contains(name))
      return false;
    return !registry.at(name).expired();
  };
  
public:

  void remove(const std::string& name) {
    if (hasAsset(name)) {
      registry[name] = std::shared_ptr<T>();
    }
  }

  std::shared_ptr<const T> get(const std::string& name) {
    if (hasAsset(name)) {
      std::weak_ptr<const T> ref = registry.at(name);
      return ref.lock();
    }

    std::shared_ptr<const T> asset = loadAsset(name);
    if (asset != nullptr) {
      registry[name] = asset;
    }

    return asset;
  };

  virtual ~AssetRegistry() = default;
};