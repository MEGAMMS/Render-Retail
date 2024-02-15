#pragma once

#include "core.h"
#include "shaderClass.h"
#include "buffers/VAO.h"

class SquarePlayer {
private:

    VAO VAO1;
    std::shared_ptr<Shader> shaderProgram;

    GLuint timeUniID;
    GLuint resUniID;
    GLuint moveUniID;

    bool move = 0;
    float pos = 0;

public:
    SquarePlayer();
    void update(float dt);

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};