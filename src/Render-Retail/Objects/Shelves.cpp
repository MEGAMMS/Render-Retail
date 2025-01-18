#include "Render-Retail/Objects/Shelves.h"

#include <memory>

#include "Objects/Object.h"

Shelves::Shelves() {
    for (int i = 0; i < 3; ++i) {
        m_shelves.push_back(std::make_shared<Box>());
        shelfVisibility.push_back(1);
    }
    for (int i = 0; i < 3; ++i) {
        m_shelves[i]->setParent(std::shared_ptr<Object>(this));
        m_shelves[i]->setSize(glm::vec3(2., 0.5, 8.));
    }

    m_shelves[0]->setPosition(glm::vec3(0));
    m_shelves[0]->setOrientation(glm::vec3(0,0,1));

    m_shelves[1]->setPosition(glm::vec3(0));
    m_shelves[1]->setOrientation(glm::vec3(1., 0, 0));
    m_shelves[1]->setSize(glm::vec3(2.5, 0.5, 8.));

    m_shelves[2]->setPosition(glm::vec3(6, 0, 0));
    m_shelves[2]->setOrientation(glm::vec3(0.,0,1));
}

void Shelves::update(float dt) {}
void Shelves::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    for (int i = 0; i < 3; ++i) {
        if (!shelfVisibility[i]) continue;
        m_shelves[i]->render(mvp, lightPos, lightColor, viewPos);
    }
}

void Shelves::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Shelves::onCursorPositionEvent(double x, double y) {}

void Shelves::setShelfVisibility(Shelf shelf, bool visible) { shelfVisibility[static_cast<int>(shelf)] = visible; }

void Shelves::setTexture(const std::string& texturePath) {
    for (const auto& shelf : m_shelves) {
        shelf->setTexture(texturePath);
    }
}

void Shelves::setShelfTexture(Shelf shelf, const std::string& texturePath) {
    m_shelves[static_cast<int>(shelf)]->setTexture(texturePath);
}