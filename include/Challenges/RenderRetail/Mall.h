#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"

class Mall
{
    public:
        Mall();
        void update(float dt);
        void render(glm::mat4 mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);

        void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
        void onCursorPositionEvent(double x, double y);
    private:
        
};