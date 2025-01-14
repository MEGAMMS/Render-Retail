#include "Render-Retail/ClothingStore.h"

#include <memory>

#include "Objects/Object.h"

ClothingStore::ClothingStore() {
    m_room = std::make_shared<StoreWalls>();
    m_room->setParent(std::shared_ptr<Object>(this));
    m_room->setPosition(glm::vec3(4));
    // m_room->setSize(glm::vec3(5.));
    // m_room->setOrientation(glm::vec3(-1.));
    // m_room->setTexture("assets/brick.png");
    m_room->setWallTexture(Wall::Back, "assets/test-textures/default_stone_brick.png");

    m_desk = std::make_shared<Table>();
    m_desk->setParent(std::shared_ptr<Object>(this));
    m_desk->setPosition(glm::vec3(5., 0., 7.));
    m_desk->setSize(glm::vec3(4., 2., 2.));
}

void ClothingStore::update(float dt) {}
void ClothingStore::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    // m_room->render(mvp, lightPos, lightColor, viewPos);
    m_desk->render(mvp, lightPos, lightColor, viewPos);
}
void ClothingStore::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void ClothingStore::onCursorPositionEvent(double x, double y) {}
