#include "AngryNeighbor/Plane.h"
#include "AssetManager/AssetManager.h"

Plane::Plane(glm::vec3 position, glm::vec2 size, glm::vec3 orientation, glm::vec3 color) :
    position(position), size(size), orientation(orientation), color(color) {

    static std::vector<Plane::Vertex> vertices = {
      Vertex{ glm::vec3{0.,0.,0.} ,glm::vec2{0,0} },
      Vertex{ glm::vec3{1.,0.,0.} ,glm::vec2{1,0}},
      Vertex{ glm::vec3{0.,1.,0.} ,glm::vec2{0,1}},
      Vertex{ glm::vec3{1.,1.,0.} ,glm::vec2{1,1}}
    };
    static std::vector<GLuint> indices = {
        0, 1, 2,
        1, 2, 3
    };
    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(Plane::Vertex::vertexAttributes(), sizeof(Plane::Vertex));
    shaderProgram = AssetManager::instance().loadShaderProgram("Plane");
    // Compute the model matrix
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);



    // model = glm::rotate(model, glm::radians(45.f), glm::vec3(1., 0., 0.));
    // Step 2: Rotate the plane to align with the given orientation

    glm::vec3 defaultNormal(0.f, 0.f, 1.f); // Assuming the plane initially faces the +Z direction
    orientation = glm::normalize(orientation);
    glm::vec3 axis = glm::cross(defaultNormal, orientation);
    float angle = glm::acos(glm::dot(defaultNormal, orientation));

    std::cerr << axis.x << " " << axis.y << " " << axis.z << std::endl;
    std::cerr << glm::length(axis) << " " << glm::degrees(angle) << std::endl;
    if (glm::length(axis) > 0.0001f) { // Avoid invalid axis when vectors are aligned
        model = glm::rotate(model, angle, glm::normalize(axis));
    }

    model = glm::scale(model, glm::vec3(size, 1.0f));
}

void Plane::update(float dt) {
}

void Plane::render(glm::mat4& mvp) {
    shaderProgram->setMat4("MVP", mvp);
    shaderProgram->setMat4("model", model);
    shaderProgram->setVec3("color", color);
    shaderProgram->activate();
    vertexArray->renderIndexed();
}

void Plane::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
}
