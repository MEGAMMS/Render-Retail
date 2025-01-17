#include "Render-Retail/Objects/Elevator.h"

Elevator::Elevator(float highet) {
    status.highet = highet;
    status.speed = highet / 2;
    m_root = std::make_shared<Object>();
    m_root->setParent(std::shared_ptr<Object>(this));

    m_body = std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(m_root));
    m_body->setFaceVisibility(Face::Back, false);
    m_body->setSize(glm::vec3(1, 2, 1));

    m_door = std::make_shared<Door>();
    m_door->setParent(std::shared_ptr<Object>(m_root));
    m_door->setPosition(glm::vec3(0, 0, 1));
}

void Elevator::update(float dt) {
    status.update(dt);
    m_root->setPosition(glm::vec3(0, status.currentHighet, 0));

    m_door->update(dt);
}
void Elevator::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
    m_door->render(mvp, lightPos, lightColor, viewPos);
}
void Elevator::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
    if (key == GLFW_KEY_U and pressed) status.chagneStatus();
    m_door->onKeyEvent(key, scancode, action, mode);
}
void Elevator::onCursorPositionEvent(double x, double y) {}
