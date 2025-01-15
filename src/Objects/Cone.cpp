#include "Objects/Cone.h"

#include "AssetManager/AssetManager.h"
#include "glm/detail/type_vec.hpp"

Cone::Cone(float height, float topDiameter, float bottomDiameter, int resolution) {
    this->defaultOrientation = glm::vec3(0.0, 1.0, 0.0);
    generateGeometry(height, topDiameter, bottomDiameter, resolution);
    vertexArray->addVertexAttributes(Cone::Vertex::vertexAttributes(), sizeof(Cone::Vertex));
    shaderProgram = AssetManager::instance().loadShaderProgram("Cone");
    color = glm::vec3(0.6, 1, 1);
    topTexture = nullptr;
    bottomTexture = nullptr;
    topBaseVisible = true;
    bottomBaseVisible = true;
}

void Cone::generateGeometry(float height, float topDiameter, float bottomDiameter, int resolution) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
 
    float topRadius = topDiameter / 2.0f;
    float bottomRadius = bottomDiameter / 2.0f;
    glm::vec3 topCenter(0.0f, height / 2.0f, 0.0f);
    glm::vec3 bottomCenter(0.0f, -height / 2.0f, 0.0f);

    // Generate top and bottom circle vertices
    for (int i = 0; i < resolution; ++i) {
        float angle = (2.0f * glm::pi<float>() * i) / resolution;
        glm::vec3 position = topCenter + glm::vec3(topRadius * cos(angle), 0.0f, topRadius * sin(angle));
        vertices.push_back({position,
                            {0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle)},
                            glm::normalize(glm::vec3(cos(angle), 0.0f, sin(angle)))});
    }

    for (int i = 0; i < resolution; ++i) {
        float angle = (2.0f * glm::pi<float>() * i) / resolution;
        glm::vec3 position = bottomCenter + glm::vec3(bottomRadius * cos(angle), 0.0f, bottomRadius * sin(angle));
        vertices.push_back({position,
                            {0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle)},
                            glm::normalize(glm::vec3(cos(angle), 0.0f, sin(angle)))});
    }

    // Add indices for side faces
    for (int i = 0; i < std::max(resolution, resolution); ++i) {
        uint32_t topIdx = i % resolution;
        uint32_t bottomIdx = (i % resolution) + resolution;
        uint32_t nextTopIdx = (i + 1) % resolution;
        uint32_t nextBottomIdx = ((i + 1) % resolution) + resolution;

        indices.insert(indices.end(), {topIdx, bottomIdx, nextTopIdx, nextTopIdx, bottomIdx, nextBottomIdx});
    }

    // Add indices for top base
    uint32_t centerIdx = vertices.size();
    vertices.push_back({topCenter, {0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}});
    for (uint32_t i = 0; i < resolution; ++i) {
        uint32_t nextIdx = (i + 1) % resolution;
        indices.insert(indices.end(), {centerIdx, i, nextIdx});
    }

    // Add indices for bottom base
    centerIdx = vertices.size();
    vertices.push_back({bottomCenter, {0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}});
    for (uint32_t i = 0; i < resolution; ++i) {
        uint32_t nextIdx = (i + 1) % resolution + resolution;
        indices.insert(indices.end(), {centerIdx, nextIdx, i + resolution});
    }

    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    m_indicesCount = indices.size();
    m_resolution = resolution;
}

void Cone::setTexture(const std::string& topTexturePath, const std::string& bottomTexturePath) {
    if (topTexturePath == "")
        topTexture = nullptr;
    else
        topTexture = AssetManager::instance().loadTexture(topTexturePath);
    if (bottomTexturePath == "")
        bottomTexture = nullptr;
    else
        bottomTexture = AssetManager::instance().loadTexture(bottomTexturePath);
}

void Cone::setColor(glm::vec3 in_Color) { color = in_Color; }

void Cone::setBaseVisibility(bool topVisible, bool bottomVisible) {
    topBaseVisible = topVisible;
    bottomBaseVisible = bottomVisible;
}

void Cone::update(float dt) {}

void Cone::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    shaderProgram->activate();
    shaderProgram->setMat4("MVP", mvp);
    shaderProgram->setVec3("lightPos", lightPos);
    shaderProgram->setVec3("lightColor", lightColor);
    shaderProgram->setVec3("viewPos", viewPos);
    shaderProgram->setMat4("model", this->getModel());
    shaderProgram->setVec3("scale", size);
    shaderProgram->setVec3("u_color", color);

    shaderProgram->setFloat("u_useTexture", false);
    vertexArray->renderSubIndexed(m_indicesCount - 2 * (3 * (m_resolution)), 0);

    shaderProgram->setFloat("u_useTexture", topTexture != nullptr);
    if (topTexture != nullptr) shaderProgram->setTexture("textureSlot", topTexture, 8);
    if (topBaseVisible) vertexArray->renderSubIndexed(3 * m_resolution, m_indicesCount - 2 * (3 * (m_resolution)));

    shaderProgram->setFloat("u_useTexture", bottomTexture != nullptr);
    if (bottomTexture != nullptr) shaderProgram->setTexture("textureSlot", bottomTexture, 8);
    if (bottomBaseVisible) vertexArray->renderSubIndexed(3 * m_resolution, m_indicesCount - 3 * (m_resolution));
}

void Cone::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
