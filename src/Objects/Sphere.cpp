#include "Objects/Sphere.h"

#include <cmath>
#include <vector>

#include "AssetManager/AssetManager.h"
#include "glm/detail/type_vec.hpp"

Sphere::Sphere(int resolution) {
    this->defaultOrientation = glm::vec3(0.0f, 1.0f, 0.0f);
    generateGeometry(resolution);
    vertexArray->addVertexAttributes(Sphere::Vertex::vertexAttributes(), sizeof(Sphere::Vertex));
    shaderProgram = AssetManager::instance().loadShaderProgram("Sphere");
    color = glm::vec3(0.6f, 1.0f, 1.0f);
    texture = nullptr;
}

void Sphere::generateGeometry(int resolution) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    for (int i = 0; i <= resolution; ++i) {
        float theta = glm::pi<float>() * i / resolution;
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);

        for (int j = 0; j <= resolution; ++j) {
            float phi = 2 * glm::pi<float>() * j / resolution;
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);

            glm::vec3 position(sinTheta * cosPhi, cosTheta, sinTheta * sinPhi);

            glm::vec2 texCoord(static_cast<float>(j) / resolution, static_cast<float>(i) / resolution);

            glm::vec3 normal = glm::normalize(position);
            vertices.push_back({position, texCoord, normal});
        }
    }

    for (int i = 0; i < resolution; ++i) {
        for (int j = 0; j < resolution; ++j) {
            int first = i * (resolution + 1) + j;
            int second = first + resolution + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    vertexArray = std::make_shared<VertexArray>(vertices, indices);
}

void Sphere::setTexture(const std::string &texturePath) {
    if (texturePath.empty()) {
        texture = nullptr;
    } else {
        texture = AssetManager::instance().loadTexture(texturePath);
    }
}

void Sphere::setColor(glm::vec3 newColor) { color = newColor; }

void Sphere::render(glm::mat4 &mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    shaderProgram->activate();
    shaderProgram->setMat4("MVP", mvp);
    shaderProgram->setVec3("lightPos", lightPos);
    shaderProgram->setVec3("lightColor", lightColor);
    shaderProgram->setVec3("viewPos", viewPos);
    shaderProgram->setMat4("model", this->getModel());
    shaderProgram->setVec3("scale", size);
    shaderProgram->setVec3("u_color", color);

    shaderProgram->setFloat("u_useTexture", texture != nullptr);

    if (texture != nullptr) {
        shaderProgram->setTexture("textureSlot", texture, 8);
    }

    vertexArray->renderIndexed();
}

void Sphere::update(float dt) {}

void Sphere::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
