#include "Render-Retail/ClothingStore.h"

#include <memory>

#include "Objects/Object.h"

ClothingStore::ClothingStore() {
    m_room = std::make_shared<Box>();
    m_room->setParent(std::shared_ptr<Object>(this));
    m_room->setPosition(glm::vec3(-4));
    m_room->setSize(glm::vec3(5.));
    // m_room->setOrientation(glm::vec3(-1.));
    // m_room->setTexture("assets/brick.png");
    m_room->setFaceTexture(Face::Front, "assets/brick.png");
    m_room->setFaceVisibility(Face::Right, false);
}

void ClothingStore::update(float dt) {}
void ClothingStore::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_room->render(mvp, lightPos, lightColor, viewPos);
}
void ClothingStore::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void ClothingStore::onCursorPositionEvent(double x, double y) {}