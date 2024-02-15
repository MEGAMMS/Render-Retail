#pragma once

#include "core.h"
#include "shaderClass.h"
#include "buffers/VAO.h"

class SquarePlayer {
private:

    VAO vao;
    std::shared_ptr<Shader> shaderProgram;

    GLuint timeUniID;
    GLuint resUniID;
    GLuint moveUniID;

    const float SPEED = 1.;
    glm::vec2 move = { 0.,0. };
    glm::vec2 pos = {0.,0.};

public:
    SquarePlayer();
    void update(float dt);
    void Delete();

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};