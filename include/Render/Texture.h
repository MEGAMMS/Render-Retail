#pragma once

#include "core.h"
#include "Render/Image.h"

class Texture {
  uint32_t id = 0;
  uint32_t type;

public:
  Texture(const Texture&) = delete;
  Texture(Texture&) = delete;
  Texture(Texture&&) = delete;

  Texture(uint32_t type);

  [[nodiscard]] bool isValid() const { return id != 0; };

  void bind() const;
  void bindToSlot(uint32_t slot) const;
  void unbind() const;

  void buffer2DRGBAData(const Image& image);
  void bufferCubeMapRGBAData(const std::array<std::shared_ptr<const Image>, 6>& images);

  ~Texture();

  static std::shared_ptr<const Texture> loadTexture2D(const std::string& name);
  static std::shared_ptr<const Texture> loadCubeMapTexture(const std::string& name);
};
