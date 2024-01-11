cmake_minimum_required (VERSION 3.5)
project (Sandbox)

# Add source files
file(GLOB SOURCE_FILES "src/*/*.cpp" "src/*.cpp")

# Add include directories
include_directories(include)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
add_subdirectory(lib/glad EXCLUDE_FROM_ALL)

target_link_libraries(${PROJECT_NAME}
    glfw
    glad
    glm
)

# Copy shaders to build directory
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})