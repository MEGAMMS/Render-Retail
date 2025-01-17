#include "Render-Retail/ClothingStore.h"

#include <memory>

#include "Objects/Object.h"

ClothingStore::ClothingStore() {
    m_room = std::make_shared<StoreWalls>();
    m_room->setParent(std::shared_ptr<Object>(this));
    m_room->setPosition(glm::vec3(0));
    m_room->setSize(glm::vec3(1.3, 1, 1));
    // m_room->setOrientation(glm::vec3(-1.));
    m_room->setWallTexture(Wall::Down, "assets/test-textures/WoodFloor1.png",glm::vec2(2.6,1)*glm::vec2(2.));
    m_room->setWallTexture(Wall::Back, "assets/textures/pbr/wall/albedo.png",glm::vec2(2.6,1)*glm::vec2(2.));
    m_room->setWallTexture(Wall::Right, "assets/textures/pbr/wall/albedo.png",glm::vec2(2.6,1)*glm::vec2(2.));
    m_room->setWallTexture(Wall::Left, "assets/textures/pbr/wall/albedo.png",glm::vec2(2.6,1)*glm::vec2(2.));
    m_room->setWallTexture(Wall::Up, "assets/test-textures/WoodFloor1.png",glm::vec2(2.6,1)*glm::vec2(2.));

    m_frontWall = std::make_shared<FrontWall>();
    m_frontWall->setParent(std::shared_ptr<Object>(this));
    m_frontWall->setPosition(glm::vec3(0,0,10));
    m_frontWall->setSize(glm::vec3(1.3, 1, 1));
    m_frontWall->setOrientation(glm::vec3(0, 0, 1));
    m_frontWall->setTexture("assets/textures/pbr/wall/albedo.png");

    m_desk = std::make_shared<Table>();
    m_desk->setParent(std::shared_ptr<Object>(this));
    m_desk->setPosition(glm::vec3(4.8, -4., 3.));
    m_desk->setSize(glm::vec3(4., 2., 2.));
    m_desk->setTexture("assets/test-textures/default_pine_wood.png");

    m_shelf = std::make_shared<Shelves>();
    m_shelf->setParent(std::shared_ptr<Object>(this));
    m_shelf->setPosition(glm::vec3(1.3, 1.5, 3.));
    m_shelf->setSize(glm::vec3(1.3, 0.88, 0.88));
    m_shelf->setTexture("assets/test-textures/default_pine_wood.png");

    m_lamp = std::make_shared<Lamp>();
    m_lamp->setParent(std::shared_ptr<Object>(this));
    m_lamp->setPosition(glm::vec3(6, 4, 5));
    m_lamp->setCoverColor(glm::vec3(0.1, 01., 0.6));

    for (int i = 0; i < 4; i++) {
        auto cloth = std::make_shared<Clothes>(8);
        cloth->setParent(std::shared_ptr<Object>(this));
        cloth->setSize(glm::vec3(3.5));
        m_clothes.push_back(cloth);
    }
    m_clothes[0]->setPosition(glm::vec3(10.3, -1, 5));
    m_clothes[1]->setPosition(glm::vec3(3.3, -1, 5));
    m_clothes[2]->setPosition(glm::vec3(3.3, 4, 5));
    m_clothes[3]->setPosition(glm::vec3(10.3, 4, 5));
}

void ClothingStore::update(float dt) {}
void ClothingStore::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_room->render(mvp, lightPos, lightColor, viewPos);
    m_desk->render(mvp, lightPos, lightColor, viewPos);
    m_shelf->render(mvp, lightPos, lightColor, viewPos);
    m_lamp->render(mvp, lightPos, lightColor, viewPos);
    m_frontWall->render(mvp, lightPos, lightColor, viewPos);
    for (const auto& cloth : m_clothes) {
        cloth->render(mvp, lightPos, lightColor, viewPos);
    }
}
void ClothingStore::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void ClothingStore::onCursorPositionEvent(double x, double y) {}
