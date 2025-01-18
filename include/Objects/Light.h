#pragma once

#include "Objects/Object.h"
#include "Objects/Sphere.h"
#include "Render/ShaderProgram.h"
#include "core.h"

class Light : public Object {
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoord;
    };
    std::shared_ptr<const ShaderProgram> lightShader;

    glm::vec3 lightPos;
    glm::vec3 lightColor;

   public:
    std::shared_ptr<Sphere> m_sphere;

    Light(glm::vec3 lightPos, glm::vec3 lightColor);
    inline glm::vec3 getLightPos() { return lightPos; };
    inline glm::vec3 getLightColor() { return lightColor; };
    void update(float dt);
    void render(glm::mat4 mvp);

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
    void onCursorPositionEvent(double x, double y);
};
