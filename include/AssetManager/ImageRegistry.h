#pragma once

#include "Render/Image.h"
#include "AssetRegistry.h"

class ImageRegistry : public AssetRegistry<Image> {
    std::shared_ptr<const Image> loadAsset(const std::string& name) override {
        std::shared_ptr<Image> image = std::make_shared<Image>();
        uint32_t error = lodepng::decode(image->data, image->width, image->height, name, LCT_RGBA);

        if (error != 0) {
            std::cerr << "Failed to read the image file: " << name << ", message: " << lodepng_error_text(error) << std::endl;
            return nullptr;
        }
        vertical_flip(image->data, image->width, image->height);
        return image;
    }
private:
    void vertical_flip(std::vector<uint8_t>& image, uint32_t& width, uint32_t& height) {
        size_t number_of_channels = 4;
        size_t bytes_per_pixel = sizeof(uint8_t) * number_of_channels;
        size_t bytes_per_row = static_cast<size_t>(width) * bytes_per_pixel;

        for (int row = 0; row < (height >> 1); ++row) {
            auto row0 = image.begin() + row * bytes_per_row;
            auto row1 = image.begin() + (height - row - 1) * bytes_per_row;

            std::swap_ranges(row0, row0 + bytes_per_row, row1);
        }
    }
};