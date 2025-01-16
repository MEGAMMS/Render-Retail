# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)
project(stb_image)

add_library(stb_image
    stb_image.c
    include/stb_image.h
)

# Specify include directories
target_include_directories(stb_image PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
