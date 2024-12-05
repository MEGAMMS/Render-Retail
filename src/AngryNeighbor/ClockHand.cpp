#include "AngryNeighbor/ClockHand.h"
#include "AssetManager/AssetManager.h"

ClockHand::ClockHand(glm::vec3 position, float length, float scale, glm::vec3 orientation, glm::vec3 color) :
    position(position), orientation(orientation) {
    this->color = color;
    static std::vector<ClockHand::Vertex> vertices = {
              Vertex{ glm::vec3{0.,0.,0.} ,glm::vec2{0,0} },
              Vertex{ glm::vec3{1. * length,0.,0.} ,glm::vec2{1,0}},
              Vertex{ glm::vec3{0.,1.,0.} ,glm::vec2{0,1}},
              Vertex{ glm::vec3{1. * length,1.,0.} ,glm::vec2{1,1}},
              Vertex{ glm::vec3{1. * length + 0.5,0.5,0.} ,glm::vec2{1,1}}
    };
    static std::vector<GLuint> indices = {
        0, 1, 2,
        1, 2, 3,
        0, 1, 4
    };
    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(ClockHand::Vertex::vertexAttributes(), sizeof(ClockHand::Vertex));
    shaderProgram = AssetManager::instance().loadShaderProgram("Plane");
    // Compute the model matrix
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    glm::vec3 defaultNormal(0.f, 0.f, 1.f); // Assuming the plane initially faces the +Z direction
    orientation = glm::normalize(orientation);
    glm::vec3 axis = glm::cross(defaultNormal, orientation);
    float angle = glm::acos(glm::dot(defaultNormal, orientation));

    if (glm::length(axis) > 0.0001f) { // Avoid invalid axis when vectors are aligned
        model = glm::rotate(model, angle, glm::normalize(axis));
    }

    model = glm::scale(model, glm::vec3(scale));
}

void ClockHand::update(float dt) {
}

void ClockHand::render(glm::mat4& mvp) {
    shaderProgram->setMat4("MVP", mvp);
    shaderProgram->setMat4("model", model);
    shaderProgram->setVec3("color", color);
    shaderProgram->activate();
    vertexArray->renderIndexed();
}

void ClockHand::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
}
