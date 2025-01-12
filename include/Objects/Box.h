#pragma once

#include "Objects/Object.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "core.h"

enum class Face {
    Front = 0,
    Back,
    Up,
    Down,
    Left,
    Right,
};

class Box : public Object {
   private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoord;
        glm::vec3 Normal;
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
    std::vector<std::shared_ptr<const Texture>> textures;
    std::vector<bool> faceVisibility;

   public:
    Box();
    void setFaceTexture(Face face, const std::string& texturePath);
    void setTexture(const std::string& texturePath);
    void setFaceVisibility(Face face, bool visible);
    void update(float dt);
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};