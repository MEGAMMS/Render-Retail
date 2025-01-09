#pragma once

#include "core.h"
#include "core/Camera.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "Application/Scene.h"
#include "Challenges/Cubes/LightCube.h"
#include "Challenges/RenderRetail/Plain.h"
#include "Challenges/RenderRetail/Box.h"


class RenderRetail : public Scene 
{
    public:
        RenderRetail();
        void update(float dt) override;
        void render() override;
        void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
        void onCursorPositionEvent(double x, double y);
    private:
    
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;

        static std::vector<VertexAttribute> vertexAttributes() {
        return {
            {3, VertexAttribute::Float, offsetof(Vertex, position)},
            {3, VertexAttribute::Float, offsetof(Vertex, color)},
        };
        }
    };
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> shaderProgram;

    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<LightCube> m_cube;
    std::vector<std::shared_ptr<Plain>> m_plains;
    std::shared_ptr<Box> Mall;
    
    glm::mat4 m_VP=glm::mat4(1.);
};