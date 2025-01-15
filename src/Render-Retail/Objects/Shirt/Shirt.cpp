#include "Render-Retail/Objects/Shirt/Shirt.h"

#include <memory>

#include "Objects/Object.h"

Shirt::Shirt() {
    m_body = std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(this));
    m_body->setPosition(glm::vec3(0));
    m_body->setSize(glm::vec3(0.5, 0.5, 0.1));
    m_body->setTexture("assets/test-textures/red_shirt.png");

    m_sleeves = std::make_shared<ShirtSleeves>();
    m_sleeves->setParent(std::shared_ptr<Object>(this));
    m_sleeves->setSize(glm::vec3(1));
    m_sleeves->setPosition(glm::vec3(0.24,0.2,0));

}

void Shirt::update(float dt) {}
void Shirt::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
    m_sleeves->render(mvp, lightPos, lightColor, viewPos);
}
void Shirt::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Shirt::onCursorPositionEvent(double x, double y) {}