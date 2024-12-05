#pragma once

#include "core.h"
#include "Application/scene.h"
#include "Render/Shader.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "core/Camera.h"
#include "Challenges/Cubes/Cube.h"

class Cubes : public Scene {
private:
    std::shared_ptr<Camera> camera1;
    std::shared_ptr<Camera> camera2;

    std::shared_ptr<Camera> activeCamera;

    std::shared_ptr<Cube> cube;
    glm::mat4 mvp;

    
public:
    Cubes();
    void update(float dt) override;
    void render() override;

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;
};