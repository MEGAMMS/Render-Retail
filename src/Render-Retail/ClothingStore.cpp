#include "Render-Retail/ClothingStore.h"

#include <memory>

#include "Objects/Object.h"

ClothingStore::ClothingStore() {
    m_room = std::make_shared<StoreWalls>();
    m_room->setParent(std::shared_ptr<Object>(this));
    m_room->setPosition(glm::vec3(0));
    m_room->setSize(glm::vec3(1.3,1,1));
    // m_room->setOrientation(glm::vec3(-1.));
    m_room->setTexture("assets/brick.png");
    m_room->setWallTexture(Wall::Down, "assets/test-textures/WoodFloor1.png");

    m_desk = std::make_shared<Table>();
    m_desk->setParent(std::shared_ptr<Object>(this));
    m_desk->setPosition(glm::vec3(1.3, -4., 3.));
    m_desk->setSize(glm::vec3(4., 2., 2.));

    m_shelf = std::make_shared<Shelves>();
    m_shelf->setParent(std::shared_ptr<Object>(this));
    m_shelf->setPosition(glm::vec3(1.3, 1.5, 3.));
    m_shelf->setSize(glm::vec3(1.3,0.88,0.88));
    m_shelf->setTexture("assets/test-textures/default_pine_wood.png");

    m_hanger = std::make_shared<Hanger>();
    m_hanger->setParent(std::shared_ptr<Object>(this));
    m_hanger->setPosition(glm::vec3(8.3,-1, 5));

    m_shirt = std::make_shared<Shirt>();
    m_shirt->setParent(std::shared_ptr<Object>(this));
    m_shirt->setPosition(glm::vec3(7.3,-3,5));
    m_shirt->setSize(glm::vec3(3));

    m_wardrobe = std::make_shared<Wardrobe>(5);
    m_wardrobe->setParent(std::shared_ptr<Object>(this));
    m_wardrobe->setPosition(glm::vec3(0));
    m_wardrobe->setSize(glm::vec3(3));
    m_wardrobe->setTexture("assets/test-textures/Wood1.png");

    m_lamp = std::make_shared<Lamp>();
    m_lamp->setParent(std::shared_ptr<Object>(this));
    m_lamp->setPosition(glm::vec3(6,3,5));
    m_lamp->setCoverColor(glm::vec3(0.1,01.,0.6));
}

void ClothingStore::update(float dt) {}
void ClothingStore::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_room->render(mvp, lightPos, lightColor, viewPos);
    m_desk->render(mvp, lightPos, lightColor, viewPos);
    m_shelf->render(mvp, lightPos, lightColor, viewPos);
    m_hanger->render(mvp, lightPos, lightColor, viewPos);
    m_shirt->render(mvp, lightPos, lightColor, viewPos);
    m_lamp->render(mvp, lightPos, lightColor, viewPos);
    // m_wardrobe->render(mvp, lightPos, lightColor, viewPos);
}
void ClothingStore::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void ClothingStore::onCursorPositionEvent(double x, double y) {}
