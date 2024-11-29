#pragma once

#include "core.h"
#include "Render/Shader.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "core/Camera.h"

class Cubes {
private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoord;
    };
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> cubesShader;
    std::shared_ptr<const Texture> brick;

    std::shared_ptr<Camera> camera1;
    std::shared_ptr<Camera> camera2;

    std::shared_ptr<Camera> activeCamera;

public:
    Cubes();
    void update(float dt);
    void Delete();

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
    void onCursorPositionEvent(double x, double y);
};