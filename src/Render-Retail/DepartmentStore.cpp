#include "Render-Retail/DepartmentStore.h"

#include <memory>

#include "Objects/Object.h"

DepartmentStore::DepartmentStore() {
    m_room = std::make_shared<StoreWalls>();
    m_room->setParent(std::shared_ptr<Object>(this));
    m_room->setPosition(glm::vec3(0));
    m_room->setSize(glm::vec3(5, 1, 3));
    m_room->setTexture("assets/brick.png");
    m_room->setWallTexture(Wall::Down, "assets/test-textures/Wood1.png");
    m_room->setWallTexture(Wall::Back, "assets/test-textures/default_brick.png", glm::vec2(4) * glm::vec2(5, 1));
    m_room->setWallTexture(Wall::Right, "assets/test-textures/default_brick.png", glm::vec2(4) * glm::vec2(5, 1));
    m_room->setWallTexture(Wall::Left, "assets/test-textures/default_brick.png", glm::vec2(4) * glm::vec2(5, 1));
    m_room->setWallTexture(Wall::Up, "assets/test-textures/default_brick.png", glm::vec2(4) * glm::vec2(5, 1));

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            auto wardrobe = std::make_shared<Wardrobe>(3);
            wardrobe->setParent(std::shared_ptr<Object>(this));
            wardrobe->setSize(glm::vec3(0.5));
            wardrobe->setTexture("assets/textures/concreteTexture.png");
            wardrobe->setOrientation(glm::vec3((i % 2) ? -1 : 1, 0, 0));
            wardrobe->setPosition(glm::vec3(35 - (8 * j), -1.5, (i % 2) ? 26.5 - (2.5 * i) : 28 - (2.5 * i - 1)));
            m_wardrobes.push_back(wardrobe);
        }
    }

    m_desk = std::make_shared<Table>();
    m_desk->setParent(std::shared_ptr<Object>(this));
    m_desk->setPosition(glm::vec3(9.4, -4., 3.));
    m_desk->setSize(glm::vec3(4., 2., 2.));

    m_shelf = std::make_shared<Shelves>();
    m_shelf->setParent(std::shared_ptr<Object>(this));
    m_shelf->setPosition(glm::vec3(5, 1.5, 3.));
    m_shelf->setSize(glm::vec3(1.3, 0.88, 0.88));
    m_shelf->setTexture("assets/test-textures/default_pine_wood.png");
    m_shelf->setShelfVisibility(Shelf::Back, false);
    m_shelf->setShelfVisibility(Shelf::Right, false);

    m_lamp = std::make_shared<Lamp>();
    m_lamp->setParent(std::shared_ptr<Object>(this));
    m_lamp->setPosition(glm::vec3(12, 4, 5));
    m_lamp->setCoverColor(glm::vec3(0.1, 01., 0.6));
}

void DepartmentStore::update(float dt) {}
void DepartmentStore::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_room->render(mvp, lightPos, lightColor, viewPos);
    m_desk->render(mvp, lightPos, lightColor, viewPos);
    m_shelf->render(mvp, lightPos, lightColor, viewPos);
    m_lamp->render(mvp, lightPos, lightColor, viewPos);
    for (auto wardrobe : m_wardrobes) {
        wardrobe->render(mvp, lightPos, lightColor, viewPos);
    }
}
void DepartmentStore::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void DepartmentStore::onCursorPositionEvent(double x, double y) {}
