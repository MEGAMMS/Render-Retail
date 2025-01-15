#pragma once

#include "Objects/Object.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "core.h"

class Sphere : public Object {
   private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoord;
        glm::vec3 normal;

        static std::vector<VertexAttribute> vertexAttributes() {
            return {
                {3, VertexAttribute::Float, 0},
                {2, VertexAttribute::Float, 3 * sizeof(float)},
                {3, VertexAttribute::Float, 5 * sizeof(float)},
            };
        }
    };

    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> shaderProgram;
    glm::vec3 color;

    std::shared_ptr<const Texture> texture;

    void generateGeometry(int resolution);

   public:
    Sphere(int resolution);
    void setTexture(const std::string& texturePath);
    void setColor(glm::vec3 color);
    void update(float dt);
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};
