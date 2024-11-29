#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "Application/Scene.h"

class TriangleExample : public Scene{

private:
    struct Vertex {
        glm::vec2 position;
        static std::vector<VertexAttribute> vertexAttributes() {
            return {
                {2, VertexAttribute::Float, 0},
            };
        }
    };

    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> shaderProgram;
    bool upSideDown = false;

public:

    TriangleExample();
    void update(float dt) override;
    void render() override;
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;

};