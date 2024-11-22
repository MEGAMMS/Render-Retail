cmake_minimum_required (VERSION 3.5)
project (Sandbox)

set(CMAKE_CXX_STANDARD 23)

# Add source files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Add include directories
include_directories(include)

# Add executable
add_executable(main ${SOURCE_FILES})

add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
add_subdirectory(lib/glad EXCLUDE_FROM_ALL)
add_subdirectory(lib/lodepng EXCLUDE_FROM_ALL)

target_link_libraries(main
    glfw
    glad
    glm
    lodepng
)


# set a symlink to the assets dir
add_custom_command(
        TARGET main PRE_BUILD COMMAND
        ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)