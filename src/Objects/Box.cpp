#include "Objects/Box.h"
#include "AssetManager/AssetManager.h"

#include <sys/types.h>

#include <vector>

Box::Box() {
    std::vector<Box::Vertex> vertices = {
        {{0., 0., 0.}, {0., 0.}, {0.0, 0.0, 1.0}},  {{1., 0., 0.}, {1., 0.}, {0.0, 0.0, 1.0}},
        {{0., 1., 0.}, {0., 1.}, {0.0, 0.0, 1.0}},  {{1., 1., 0.}, {1., 1.}, {0.0, 0.0, 1.0}},
        {{0., 0., 1.}, {0., 0.}, {0.0, 0.0, -1.0}}, {{1., 0., 1.}, {1., 0.}, {0.0, 0.0, -1.0}},
        {{0., 1., 1.}, {0., 1.}, {0.0, 0.0, -1.0}}, {{1., 1., 1.}, {1., 1.}, {0.0, 0.0, -1.0}},
        {{0., 0., 0.}, {0., 0.}, {0.0, 1.0, .0}},   {{1., 0., 0.}, {1., 0.}, {0.0, 1.0, .0}},
        {{0., 0., 1.}, {0., 1.}, {0.0, 1.0, .0}},   {{1., 0., 1.}, {1., 1.}, {0.0, 1.0, .0}},
        {{0., 1., 0.}, {0., 0.}, {0.0, -1.0, .0}},  {{1., 1., 0.}, {1., 0.}, {0.0, -1.0, .0}},
        {{0., 1., 1.}, {0., 1.}, {0.0, -1.0, .0}},  {{1., 1., 1.}, {1., 1.}, {0.0, -1.0, .0}},
        {{1., 0., 0.}, {0., 0.}, {-1.0, 0.0, .0}},  {{1., 0., 1.}, {1., 0.}, {-1.0, 0.0, .0}},
        {{1., 1., 0.}, {0., 1.}, {-1.0, 0.0, .0}},  {{1., 1., 1.}, {1., 1.}, {-1.0, 0.0, .0}},
        {{0., 0., 0.}, {0., 0.}, {1.0, 0.0, .0}},   {{0., 0., 1.}, {1., 0.}, {1.0, 0.0, .0}},
        {{0., 1., 0.}, {0., 1.}, {1.0, 0.0, .0}},   {{0., 1., 1.}, {1., 1.}, {1.0, 0.0, .0}}};
    std::vector<GLuint> indices{0,  1,  2,  1,  2,  3,  4,  5,  6,  5,  6,  7,  8,  9,  10, 9,  10, 11,
                                12, 13, 14, 13, 14, 15, 16, 17, 18, 17, 18, 19, 20, 21, 22, 21, 22, 23};
    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(Box::Vertex::vertexAttributes(), sizeof(Box::Vertex));
    shaderProgram = AssetManager::instance().loadShaderProgram("Plane");

    // glm::vec3 defaultNormal(0.f, 0.f, 1.f);  // Assuming the plane initially faces the +Z direction
    // orientation = glm::normalize(orientation);
    // glm::vec3 axis = glm::cross(defaultNormal, orientation);
    // float angle = glm::acos(glm::dot(defaultNormal, orientation));
    //
    // if (glm::length(axis) > 0.0001f) {  // Avoid invalid axis when vectors are aligned
    //     model = glm::rotate(model, angle, glm::normalize(axis));
    // }

    texture = AssetManager::instance().loadTexture();
}

void Box::update(float dt) {}

void Box::render(glm::mat4 &mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    shaderProgram->setMat4("MVP", mvp);
    shaderProgram->setVec3("lightPos", lightPos);
    shaderProgram->setVec3("lightColor", lightColor);
    shaderProgram->setVec3("viewPos", viewPos);
    shaderProgram->setMat4("model", model);
    shaderProgram->setVec3("scale", size);
    shaderProgram->setTexture("textureSlot", texture, 1);
    shaderProgram->activate();
    vertexArray->renderIndexed();
}

void Box::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}

