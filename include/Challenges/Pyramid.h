#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "Application/Scene.h"

class Pyramid : public Scene {
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
    std::vector<glm::mat4> pyramidsModelMatrixes;

    glm::mat4 model;
    glm::mat4 view;

    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> shaderProgram;
public:
    Pyramid();
    void update(float dt) override;
    void render() override;
};