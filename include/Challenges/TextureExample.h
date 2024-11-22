#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "buffers/VAO.h"

class TextureExample {

private:
    VAO vao;
    std::shared_ptr<const ShaderProgram> shaderProgram;
    float mix_portion = 0.2f;

public:

    TextureExample();
    void update();
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);

};