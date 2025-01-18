#include "Render-Retail/FruitStore.h"

#include <memory>

#include "Objects/Object.h"

FruitStore::FruitStore() {
    m_room = std::make_shared<StoreWalls>();
    m_room->setParent(std::shared_ptr<Object>(this));
    m_room->setPosition(glm::vec3(0));
    m_room->setSize(glm::vec3(3, 1, 2));
    m_room->setTexture("assets/brick.png");
    m_room->setWallTexture(Wall::Down, "assets/textures/marble.png");
    m_room->setWallTexture(Wall::Back, "assets/test-textures/Bricks075.png", glm::vec2(4) * glm::vec2(5, 1));
    m_room->setWallTexture(Wall::Right, "assets/test-textures/Bricks075.png", glm::vec2(4) * glm::vec2(5, 1));
    m_room->setWallTexture(Wall::Left, "assets/test-textures/Bricks075.png", glm::vec2(4) * glm::vec2(5, 1));
    m_room->setWallTexture(Wall::Up, "assets/textures/marble.png", glm::vec2(4) * glm::vec2(5, 1));

    m_frontWall = std::make_shared<FrontWall>();
    m_frontWall->setParent(std::shared_ptr<Object>(this));
    m_frontWall->setPosition(glm::vec3(0, 0, 20));
    m_frontWall->setSize(glm::vec3(3, 1, 2));
    m_frontWall->setOrientation(glm::vec3(0, 0, 1));
    m_frontWall->setTexture("assets/test-textures/Bricks075.png");

    for (int i = 0; i < 9; i++) {
        auto box = std::make_shared<StoreWalls>();
        box->setParent(std::shared_ptr<Object>(this));
        box->setSize(glm::vec3(0.268, 0.3, 0.1));
        box->setTexture("assets/test-textures/default_pine_wood.png");
        box->setOrientation(glm::vec3(0, 1, 0));
        box->setPosition(glm::vec3((i < 5) ? 24 - (2.7 * i) : 24, -2, (i < 5) ? 4 : 29 - (2.7 * i)));

        m_boxes.push_back(box);

        auto leg = std::make_shared<Box>();
        leg->setParent(std::shared_ptr<Object>(this));
        leg->setSize(glm::vec3(0.2, 0.2, 3));
        leg->setTexture("assets/test-textures/default_stone_brick.png");
        leg->setOrientation(glm::vec3(0, 1, 0));
        leg->setPosition(glm::vec3((i < 5) ? 24 - (2.7 * i) : 24, -4, (i < 5) ? 4 : 29 - (2.7 * i)));

        m_legs.push_back(leg);

        // fruits
        // auto fruit = std::make_shared<Model>("assets/objects/banana/scene.gltf");
        // fruit->setParent(std::shared_ptr<Object>(this));
        // fruit->setSize(glm::vec3(0.07));
        // fruit->setOrientation(glm::vec3(0, 1, 1));
        // fruit->setPosition(glm::vec3((i >= 5) ? 3.6 - (0.275 * i) : 2.5, -0.07, (i >= 5) ? 0.5 : 1.6 - (0.275 * i)));

        // m_fruits.push_back(fruit);
    }

    m_desk = std::make_shared<Table>();
    m_desk->setParent(std::shared_ptr<Object>(this));
    m_desk->setPosition(glm::vec3(9.4, -4., 3.));
    m_desk->setSize(glm::vec3(4., 2., 2.));

    m_shelf = std::make_shared<Shelves>();
    m_shelf->setParent(std::shared_ptr<Object>(this));
    m_shelf->setPosition(glm::vec3(3, 1.5, 3.5));
    m_shelf->setSize(glm::vec3(1.3, 0.88, 0.88));
    m_shelf->setTexture("assets/test-textures/default_pine_wood.png");
    m_shelf->setShelfVisibility(Shelf::Right, false);

    m_lamp = std::make_shared<Lamp>();
    m_lamp->setParent(std::shared_ptr<Object>(this));
    m_lamp->setPosition(glm::vec3(12, 4, 5));
    m_lamp->setCoverColor(glm::vec3(0.14, 0.15, 0.18));
    m_lamp->setCableColor(glm::vec3(0.8, 0.8, 0.8));
    m_lamp->setBulbColor(glm::vec3(0.9, 0.9, 0.7));
}

void FruitStore::update(float dt) { m_frontWall->update(dt); }
void FruitStore::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_room->render(mvp, lightPos, lightColor, viewPos);
    m_desk->render(mvp, lightPos, lightColor, viewPos);
    m_shelf->render(mvp, lightPos, lightColor, viewPos);
    m_lamp->render(mvp, lightPos, lightColor, viewPos);
    m_frontWall->render(mvp, lightPos, lightColor, viewPos);
    for (auto box : m_boxes) {
        box->render(mvp, lightPos, lightColor, viewPos);
    }
    for (auto fruit : m_fruits) {
        fruit->render(mvp, lightPos, lightColor, viewPos);
    }
    for (auto leg : m_legs) {
        leg->render(mvp, lightPos, lightColor, viewPos);
    }
}
void FruitStore::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    m_frontWall->onKeyEvent(key, scancode, action, mode);
    bool pressed = action == GLFW_PRESS;
}
void FruitStore::onCursorPositionEvent(double x, double y) {}
