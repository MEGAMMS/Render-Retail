#include "core/Image.h"

void vertical_flip(std::vector<unsigned char>& image, unsigned& width, unsigned& height) {
    size_t number_of_channels = 4;
    size_t bytes_per_pixel = sizeof(unsigned char) * number_of_channels;
    size_t bytes_per_row = static_cast<size_t>(width) * bytes_per_pixel;

    for (int row = 0; row < (height >> 1); ++row) {
        auto row0 = image.begin() + row * bytes_per_row;
        auto row1 = image.begin() + (height - row - 1) * bytes_per_row;

        std::swap_ranges(row0, row0 + bytes_per_row, row1);
    }
}

Img::Img(std::string path) {

    unsigned error = lodepng::decode(data, width, height, path, LCT_RGBA);

    // Check if there's an error
    if (error) {
        std::cerr << "Decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        exit(1);
    }
    vertical_flip(data, width, height);
}

