#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "buffers/VAO.h"

class TriangleExample {

private:
    VAO vao;
    std::shared_ptr<const ShaderProgram> shaderProgram;
    bool upSideDown = false;

public:

    TriangleExample();
    void update();
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);

};