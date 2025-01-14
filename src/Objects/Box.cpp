#include "Objects/Box.h"

#include "AssetManager/AssetManager.h"

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
    shaderProgram = AssetManager::instance().loadShaderProgram("Box");
    textures.assign(6, AssetManager::instance().loadTexture());
    faceVisibility.assign(6, true);
}

void Box::setTexture(const std::string& texturePath) {
    for (int i = 0; i < 6; i++) setFaceTexture((Face)i, texturePath);
}

void Box::setFaceTexture(Face face, const std::string& texturePath) {
    textures[(int)face] = AssetManager::instance().loadTexture(texturePath);
}

void Box::setFaceVisibility(Face face, bool visible) { faceVisibility[static_cast<int>(face)] = visible; }

void Box::update(float dt) {}

void Box::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    shaderProgram->activate();
    shaderProgram->setMat4("MVP", mvp);
    shaderProgram->setVec3("lightPos", lightPos);
    shaderProgram->setVec3("lightColor", lightColor);
    shaderProgram->setVec3("viewPos", viewPos);
    shaderProgram->setMat4("model", this->getModel());
    shaderProgram->setVec3("scale", size);
    for (int i = 0; i < 6; i++) {
        if (!faceVisibility[i]) continue;
        shaderProgram->setTexture("textureSlot", textures[i], 1);
        vertexArray->renderSubIndexed(6, i * 6);
    }
}

void Box::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
