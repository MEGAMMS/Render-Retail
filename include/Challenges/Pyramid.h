#pragma once

#include "core.h"
#include "Shader.h"
#include "buffers/VAO.h"

class Pyramid {
private:

    VAO vao;
    std::shared_ptr<Shader> shaderProgram;
public:
    Pyramid();
    void update(float dt);
    void Delete();

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};