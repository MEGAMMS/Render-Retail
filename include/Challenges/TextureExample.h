#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"

class TextureExample {

private:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 textureCorr;

    };
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> shaderProgram;
    float mix_portion = 0.2f;

public:

    TextureExample();
    void update();
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);

};