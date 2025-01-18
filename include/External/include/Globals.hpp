#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.hpp"


using namespace glm;


namespace workspace {

    /* Shaders */
    class Shaders {
    public:
        inline static Shader standard;
        inline static Shader material;


        static void compile() {
            standard = Shader("assets/external/Shaders/Vertex/Standard.vert", "assets/external/Shaders/Fragment/Standard.frag");
            material = Shader("assets/external/Shaders/Vertex/Material.vert", "assets/external/Shaders/Fragment/Material.frag");
        }
    };

}