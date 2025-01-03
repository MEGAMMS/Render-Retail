#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "Application/Scene.h"

class Render_Retail
{
    public:
        Render_Retail();
        void update(float dt);
        void render() ;
        void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
    private:

};