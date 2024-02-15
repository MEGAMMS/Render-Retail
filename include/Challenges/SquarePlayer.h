#pragma once

#include "core.h"
#include "shaderClass.h"
#include "shaderClass.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "core/Window.h"
#include "Application/Application.h"

namespace SquarePlayer
{
    // Vertices coordinates
    GLfloat vertices[] =
    { //               COORDINATES                  
      -1.,-1.,
      1.,-1.,
      -1.,1.,
      1.,1.

    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        3, 1, 2
    };

    VAO VAO1;

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));
    Shader shaderProgram("assets/shaders/default.vert", "assets/shaders/default.frag");

    GLuint timeUniID;
    GLuint resUniID;
    GLuint moveUniID;

    bool move = 0;
    float pos = 0;
    void setup();
    void destroy();
    void update(float dt);
}