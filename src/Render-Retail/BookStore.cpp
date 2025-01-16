#include "Render-Retail/BookStore.h"

#include <memory>

#include "Objects/Object.h"

BookStore::BookStore() {
    m_room = std::make_shared<StoreWalls>();
    m_room->setParent(std::shared_ptr<Object>(this));
    m_room->setPosition(glm::vec3(0));
    m_room->setSize(glm::vec3(2.6, 1, 1.3));
    // m_room->setOrientation(glm::vec3(-1.));
    m_room->setTexture("assets/test-textures/Bricks092.png");
    m_room->setWallTexture(Wall::Down, "assets/test-textures/WoodFloor1.png",glm::vec2(2.6,1)*glm::vec2(2.));
    m_room->setWallTexture(Wall::Up, "assets/test-textures/WoodFloor1.png",glm::vec2(2.6,1)*glm::vec2(2.));
    m_room->setWallTexture(Wall::Back, "assets/test-textures/Bricks092.png",glm::vec2(2.6,1)*glm::vec2(2.));
    m_room->setWallTexture(Wall::Right, "assets/test-textures/Bricks092.png",glm::vec2(2.6,1)*glm::vec2(2.));
    m_room->setWallTexture(Wall::Left, "assets/test-textures/Bricks092.png",glm::vec2(2.6,1)*glm::vec2(2.));

    m_desk = std::make_shared<Table>();
    m_desk->setParent(std::shared_ptr<Object>(this));
    m_desk->setPosition(glm::vec3(5.5, -4., 4.));
    m_desk->setSize(glm::vec3(4., 2., 2.));

    for (int i = 0; i < 2; i++) {
        auto m_shelf = std::make_shared<Shelves>();
        m_shelf->setParent(std::shared_ptr<Object>(this));
        m_shelf->setPosition(glm::vec3(3.3 + (i * 10), 1.5, 3.));
        m_shelf->setShelfVisibility(Shelf::Right, 0);
        m_shelf->setShelfVisibility(Shelf::Left, 0);
        m_shelf->setSize(glm::vec3(1., 0.88, 0.88));
        m_shelf->setTexture("assets/test-textures/Wood1.png");
        m_shelves.push_back(m_shelf);
    }
    for (int i = 0; i < 3; i++) {
        auto m_lamp = std::make_shared<Lamp>();
        m_lamp->setParent(std::shared_ptr<Object>(this));
        m_lamp->setPosition(glm::vec3(6 + (i * 8), 4, 5));
        m_lamp->setCoverColor(glm::vec3(0.5, 0.3, 0));
        m_lamps.push_back(m_lamp);
    }

    for (int i = 0; i < 5; i++) {
        auto wardrobe = std::make_shared<Wardrobe>(5);
        wardrobe->setParent(std::shared_ptr<Object>(this));
        wardrobe->setSize(glm::vec3(0.5));
        wardrobe->setTexture("assets/test-textures/Wood1.png");
        wardrobe->setOrientation(glm::vec3(-1, 0, 0));
        wardrobe->setPosition(glm::vec3(23.3 - (3.5 * i), -1.5, 6));
        m_wardrobes.push_back(wardrobe);
    }
    m_wardrobes[4]->setPosition(glm::vec3(3., -1.5, 11));
    m_wardrobes[4]->setOrientation(glm::vec3(1., 0, 0));
}

void BookStore::update(float dt) {}
void BookStore::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_room->render(mvp, lightPos, lightColor, viewPos);
    m_desk->render(mvp, lightPos, lightColor, viewPos);
    for (int i = 0; i < 3; i++) {
        m_lamps[i]->render(mvp, lightPos, lightColor, viewPos);
    }
    for (int i = 0; i < 2; i++) {
        m_shelves[i]->render(mvp, lightPos, lightColor, viewPos);
    }

    for (int i = 0; i < 5; i++) {
        m_wardrobes[i]->render(mvp, lightPos, lightColor, viewPos);
    }
}
void BookStore::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void BookStore::onCursorPositionEvent(double x, double y) {}
