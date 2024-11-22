#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "buffers/VAO.h"

class SquarePlayer {
private:

    VAO vao;
    std::shared_ptr<const ShaderProgram> shaderProgram;

    const glm::vec2 playerSpeed = { 5,5 };

    glm::bvec4 move = { 0,0,0,0 };
    glm::vec2 pos = { 0.,0. };

    bool rotate = false;
    float degree = 0.0f;

public:
    SquarePlayer();
    void update(float dt);
    void Delete();

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};