#pragma once

#include "core.h"
#include "Application/scene.h"
#include "Render/Shader.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "core/Camera.h"

class Cubes : public Scene{
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

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;
public:
    Cubes();
    void update(float dt) override;
    void render() override;

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;
};