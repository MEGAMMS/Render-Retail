#pragma once
#include "core.h"


class Img {
public:
    std::vector<unsigned char> data; // Image buffer
    unsigned width, height;
    Img(std::string path);

};