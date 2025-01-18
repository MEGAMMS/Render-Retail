#include "Render-Retail/Objects/Wardrobe.h"

#include <memory>

#include "Objects/Object.h"

Wardrobe::Wardrobe(unsigned int ShelfCount) {
    m_body = std::make_shared<StoreWalls>();
    m_body->setParent(std::shared_ptr<Object>(this));
    m_body->setPosition(glm::vec3(0));
    m_body->setSize(glm::vec3(1, 1, 0.25));

    float space = 1. / (ShelfCount);
    for (int i = 0; i < ShelfCount; i++) {
        auto shelf = std::make_shared<Shelves>();
        shelf->setParent(std::shared_ptr<Object>(this));
        shelf->setTexture("assets/test-textures/Wood1.png");
        shelf->setSize(glm::vec3(1));
        shelf->setShelfVisibility(Shelf::Left, 0);
        shelf->setShelfVisibility(Shelf::Right, 0);
        shelf->setPosition(glm::vec3(1,5-(space*(i+1)*8), 2.5));
        m_shelves.push_back(shelf);
    }
}

void Wardrobe::update(float dt) {}
void Wardrobe::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
    for (const auto& shelf : m_shelves) {
        shelf->render(mvp, lightPos, lightColor, viewPos);
    }
    
}
void Wardrobe::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Wardrobe::onCursorPositionEvent(double x, double y) {}

void Wardrobe::setTexture(const std::string& texturePath)
{   
    m_body->setTexture(texturePath);
    for (const auto& shelf : m_shelves) {
        shelf->setTexture(texturePath);
    }
}