#include "Render-Retail/ClothingStore.h"

#include <memory>

#include "Objects/Object.h"

ClothingStore::ClothingStore() {
    m_room = std::make_shared<StoreWalls>();
}

void ClothingStore::update(float dt) {}
void ClothingStore::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_room->render(mvp, lightPos, lightColor, viewPos);
}
void ClothingStore::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void ClothingStore::onCursorPositionEvent(double x, double y) {}