#include "Render-Retail/Objects/Elevator.h"

Elevator::Elevator() { m_body = std::make_shared<Box>(); }

void Elevator::update(float dt) {}
void Elevator::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
}
void Elevator::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Elevator::onCursorPositionEvent(double x, double y) {}
