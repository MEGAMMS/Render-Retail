#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"

class Pyramid {
private:
    struct Vertex {
    public:
        glm::vec3 position;
        glm::vec2 texCoord;
        static std::vector<VertexAttribute> vertexAttributes() {
            return {
                {3, VertexAttribute::Float, 0},
                {2, VertexAttribute::Float, 3 * sizeof(float)},
            };
        }
    };

    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> shaderProgram;
public:
    Pyramid();
    void update(float dt);
    void Delete();

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};