#include "Render-Retail/Objects/Elevator.h"

#include "GLFW/glfw3.h"

Elevator::Elevator() {
    m_body = std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(this));
}

void Elevator::update(float dt) {
    status.update(dt);
    this->setPosition(glm::vec3(0, status.currentHighet, 0));
}
void Elevator::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
}
void Elevator::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
    if (key == GLFW_KEY_U and pressed) status.chagneStatus();
}
void Elevator::onCursorPositionEvent(double x, double y) {}
