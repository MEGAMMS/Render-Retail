#include "AngryNeighbor/Box.h"
#include "AssetManager/AssetManager.h"

Box::Box(glm::vec3 position, glm::vec3 size, glm::vec3 orientation, std::vector<int>& facesToRender) :
    position(position), size(size), orientation(orientation) {

    auto [vertices, indices] = generateVerticesAndIndices(facesToRender);
    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(Box::Vertex::vertexAttributes(), sizeof(Box::Vertex));
    shaderProgram = AssetManager::instance().loadShaderProgram("Plane");
    // Compute the model matrix
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    glm::vec3 defaultNormal(0.f, 0.f, 1.f); // Assuming the plane initially faces the +Z direction
    orientation = glm::normalize(orientation);
    glm::vec3 axis = glm::cross(defaultNormal, orientation);
    float angle = glm::acos(glm::dot(defaultNormal, orientation));

    std::cerr << axis.x << " " << axis.y << " " << axis.z << std::endl;
    std::cerr << glm::length(axis) << " " << glm::degrees(angle) << std::endl;
    if (glm::length(axis) > 0.0001f) { // Avoid invalid axis when vectors are aligned
        model = glm::rotate(model, angle, glm::normalize(axis));
    }

    model = glm::scale(model, glm::vec3(size));
}

Box::Box(glm::vec3 position, glm::vec3 size, glm::vec3 orientation, std::vector<int> facesToRender, glm::vec3 color) :
    Box(position, size, orientation, facesToRender) {
    this->color = color;
}
Box::Box(glm::vec3 position, glm::vec3 size, glm::vec3 orientation, std::vector<int> facesToRender, const std::string& textureName) :
    Box(position, size, orientation, facesToRender) {
    useTexture = 1;
    texture = AssetManager::instance().loadTexture(textureName);

}
void Box::update(float dt) {
}

void Box::render(glm::mat4& mvp) {
    shaderProgram->setMat4("MVP", mvp);
    shaderProgram->setMat4("model", model);
    shaderProgram->setVec3("color", color);
    shaderProgram->setVec2("scale", size);
    shaderProgram->setInt("useTexture", useTexture);
    if (useTexture)shaderProgram->setTexture("textureSlot", texture, 1);
    shaderProgram->activate();
    vertexArray->renderIndexed();
}

void Box::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
}

// Function to generate vertices and indices based on selected faces
std::pair<std::vector<Box::Vertex>, std::vector<GLuint>> Box::generateVerticesAndIndices(std::vector<int>& facesToRender) {
    // Original face data (6 faces, each with 4 vertices)
    std::vector<std::vector<Box::Vertex>> facesVertices = {
        { // Face 1
            {glm::vec3{0., 0., 0.}, glm::vec2{0., 0.}},
            {glm::vec3{1., 0., 0.}, glm::vec2{1., 0.}},
            {glm::vec3{0., 1., 0.}, glm::vec2{0., 1.}},
            {glm::vec3{1., 1., 0.}, glm::vec2{1., 1.}}
        },
        { // Face 2
            {glm::vec3{0., 0., 1.}, glm::vec2{0., 0.}},
            {glm::vec3{1., 0., 1.}, glm::vec2{1., 0.}},
            {glm::vec3{0., 1., 1.}, glm::vec2{0., 1.}},
            {glm::vec3{1., 1., 1.}, glm::vec2{1., 1.}}
        },
        { // Face 3
            {glm::vec3{0., 0., 1.}, glm::vec2{0., 0.}},
            {glm::vec3{1., 0., 1.}, glm::vec2{1., 0.}},
            {glm::vec3{0., 0., 0.}, glm::vec2{0., 1.}},
            {glm::vec3{1., 0., 0.}, glm::vec2{1., 1.}}
        },
        { // Face 4
            {glm::vec3{0., 1., 1.}, glm::vec2{0., 0.}},
            {glm::vec3{1., 1., 1.}, glm::vec2{1., 0.}},
            {glm::vec3{0., 1., 0.}, glm::vec2{0., 1.}},
            {glm::vec3{1., 1., 0.}, glm::vec2{1., 1.}}
        },
        { // Face 5
            {glm::vec3{1., 0., 0.}, glm::vec2{0., 0.}},
            {glm::vec3{1., 0., 1.}, glm::vec2{1., 0.}},
            {glm::vec3{1., 1., 0.}, glm::vec2{0., 1.}},
            {glm::vec3{1., 1., 1.}, glm::vec2{1., 1.}}
        },
        { // Face 6
            {glm::vec3{0., 0., 0.}, glm::vec2{0., 0.}},
            {glm::vec3{0., 0., 1.}, glm::vec2{1., 0.}},
            {glm::vec3{0., 1., 0.}, glm::vec2{0., 1.}},
            {glm::vec3{0., 1., 1.}, glm::vec2{1., 1.}}
        }
    };

    // Indices for each face (two triangles per face)
    std::vector<std::vector<GLuint>> facesIndices = {
        {0, 1, 2, 1, 2, 3}, // Face 1
        {0, 1, 2, 1, 2, 3}, // Face 2
        {0, 1, 2, 1, 2, 3}, // Face 3
        {0, 1, 2, 1, 2, 3}, // Face 4
        {0, 1, 2, 1, 2, 3}, // Face 5
        {0, 1, 2, 1, 2, 3}  // Face 6
    };

    std::vector<Box::Vertex> vertices;
    std::vector<GLuint> indices;
    GLuint offset = 0;

    for (int face : facesToRender) {
        if (face < 1 || face > 6) continue;

        // Add vertices for this face
        for (const auto& vertex : facesVertices[face - 1]) {
            vertices.push_back(vertex);
        }

        // Add indices for this face
        for (const auto& index : facesIndices[face - 1]) {
            indices.push_back(offset + index);
        }

        offset += 4; // Each face has 4 vertices
    }

    return { vertices, indices };
}
