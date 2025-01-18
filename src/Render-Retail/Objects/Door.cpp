#include "Render-Retail/Objects/Door.h"

Door::Door(float highet) {
    status.openDegree = highet;
    status.speed = highet;
    m_body = std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(this));
    m_body->setSize(glm::vec3(1., 2., 0.1));
}

void Door::update(float dt) {
    status.update(dt);
    m_body->setPosition(glm::vec3(status.currentDegree, 0, 0));
}
void Door::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
}
void Door::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
    if (key == GLFW_KEY_U and pressed) status.chagneStatus();
}
void Door::setTexture(const std::string& texturePath, glm::vec2 textureScale) {
    m_body->setTexture(texturePath, textureScale);
}
void Door::onCursorPositionEvent(double x, double y) {}
