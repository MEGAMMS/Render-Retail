#pragma once

#include "core.h"
#include "Render/Shader.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"


class Cubes {
private:
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> cubesShader;
public:
    Cubes();
    void update(float dt);
    void Delete();

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};