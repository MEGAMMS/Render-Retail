#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"

class LightCube {
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoord;
    };
    std::vector<LightCube::Vertex> vertices{
          { glm::vec3{-1.,-1.,-1.} },
          { glm::vec3{ 1.,-1.,-1.} },
          { glm::vec3{-1., 1.,-1.} },
          { glm::vec3{ 1., 1.,-1.} },

          { glm::vec3{-1.,-1., 1.} },
          { glm::vec3{ 1.,-1., 1.} },
          { glm::vec3{-1., 1., 1.} },
          { glm::vec3{ 1., 1., 1.} },

          { glm::vec3{-1.,-1., 1.} },
          { glm::vec3{ 1.,-1., 1.} },
          { glm::vec3{-1.,-1.,-1.} },
          { glm::vec3{ 1.,-1.,-1.} },

          { glm::vec3{-1., 1., 1.} },
          { glm::vec3{ 1., 1., 1.} },
          { glm::vec3{-1., 1.,-1.} },
          { glm::vec3{ 1., 1.,-1.} },

          { glm::vec3{ 1.,-1.,-1.} },
          { glm::vec3{ 1.,-1., 1.} },
          { glm::vec3{ 1., 1.,-1.} },
          { glm::vec3{ 1., 1., 1.} },

          { glm::vec3{-1.,-1.,-1.} },
          { glm::vec3{-1.,-1., 1.} },
          { glm::vec3{-1., 1.,-1.} },
          { glm::vec3{-1., 1., 1.} },
    };
    std::vector<GLuint> indices{
        0, 1 ,2,
        1, 2 ,3,

        4, 5 ,6,
        5, 6 ,7,

        8, 9 ,10,
        9, 10 ,11,

        12, 13 ,14,
        13, 14 ,15,

        16, 17 ,18,
        17, 18 ,19,

        20, 21 ,22,
        21, 22 ,23
    };

    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> lightShader;

    glm::mat4 model;
    glm::vec3 lightPos;
    glm::vec3 lightColor;

public:
    LightCube(glm::vec3 lightPos, glm::vec3 lightColor);
    inline glm::vec3 getLightPos() { return lightPos; };
    inline glm::vec3 getLightColor() { return lightColor; };
    void update(float dt);
    void render(glm::mat4 mvp);

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
    void onCursorPositionEvent(double x, double y);
};
