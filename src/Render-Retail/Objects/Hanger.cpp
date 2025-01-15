#include "Render-Retail/Objects/Hanger.h"

#include <memory>

#include "Objects/Object.h"

Hanger::Hanger() {
    m_body = std::make_shared<Cone>(8, 0.25, 0.25, 100);
    m_body->setParent(std::shared_ptr<Object>(this));
    m_body->setPosition(glm::vec3(0));
    m_body->setSize(glm::vec3(1));
    m_body->setOrientation(glm::vec3(0., 0., 1.));
    m_body->setColor(glm::vec3(0.5));
}

void Hanger::update(float dt) {}
void Hanger::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
}
void Hanger::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Hanger::onCursorPositionEvent(double x, double y) {}