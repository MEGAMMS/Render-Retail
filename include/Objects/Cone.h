#pragma once

#include "Objects/Object.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "core.h"
#include "glm/detail/type_vec.hpp"

class Cone : public Object {
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

    std::shared_ptr<const Texture> topTexture;
    std::shared_ptr<const Texture> bottomTexture;
    bool topBaseVisible;
    bool bottomBaseVisible;

    void generateGeometry(float height, float topDiameter, float bottomDiameter, int resolution);
    int m_indicesCount;
    int m_resolution;

   public:
    Cone(float height, float topDiameter, float bottomDiameter, int resolution);
    void setTexture(const std::string& topTexturePath, const std::string& bottomTexturePath);
    void setBaseVisibility(bool topVisible, bool bottomVisible);
    void setColor(glm::vec3 color);
    void update(float dt);
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};
