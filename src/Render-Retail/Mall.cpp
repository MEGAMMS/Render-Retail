#include "Render-Retail/Mall.h"

#include <memory>

#include "Objects/Object.h"
#include "glm/detail/type_vec.hpp"

Mall::Mall() {
    m_body = std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(this));
    m_body->setPosition(glm::vec3(0));
    m_body->setSize(glm::vec3(120., 20, 90));
    // m_body->setOrientation(glm::vec3(0));
    m_body->setTexture("assets/brick.png");
    m_body->setFaceTexture(Face::Down, "assets/test-textures/WoodFloor1.png", glm::vec2(2.6, 1) * glm::vec2(2.));
    m_body->setFaceTexture(Face::Up, "assets/test-textures/WoodFloor1.png", glm::vec2(2.6, 1) * glm::vec2(2.));
    m_body->setFaceVisibility(Face::Back, 0);

    m_frontWall = std::make_shared<FrontWall>();
    m_frontWall->setParent(std::shared_ptr<Object>(this));
    m_frontWall->setPosition(glm::vec3(0, 10, 90));
    m_frontWall->setSize(glm::vec3(12., 2, 6));
    m_frontWall->setOrientation(glm::vec3(0, 0, 1));
    // m_frontWall->setTexture("assets/textures/pbr/wall/albedo.png");

    m_storey2 = std::make_shared<Box>();
    m_storey2->setParent(std::shared_ptr<Object>(this));
    m_storey2->setPosition(glm::vec3(0, 20.1, 0));
    m_storey2->setSize(glm::vec3(120., 20, 90));
    // m_storey2->setOrientation(glm::vec3(0));
    m_storey2->setTexture("assets/brick.png");
    m_storey2->setFaceTexture(Face::Down, "assets/test-textures/WoodFloor1.png", glm::vec2(2.6, 1) * glm::vec2(2.));
    m_storey2->setFaceTexture(Face::Up, "assets/test-textures/WoodFloor1.png", glm::vec2(2.6, 1) * glm::vec2(2.));

    for (int i = 0; i <2; i++) {
        auto m_wall = std::make_shared<Box>();
        m_wall->setParent(std::shared_ptr<Object>(this));
        m_wall->setSize(glm::vec3(9, 20,16));
        m_wall->setTexture("assets/test-textures/WoodFloor1.png");
        m_walls.push_back(m_wall);
    }

    m_clothingStore = std::make_shared<ClothingStore>();
    m_clothingStore->setParent(std::shared_ptr<Object>(this));
    m_clothingStore->setPosition(glm::vec3(0.1, 9, 29));
    m_clothingStore->setSize(glm::vec3(2.2, 1.8, 1.5));
    m_clothingStore->setOrientation(glm::vec3(1, 0, 0));

    m_walls[0]->setOrientation(glm::vec3(1, 0, 0));
    m_walls[0]->setPosition(glm::vec3(0.1, 0, 38));

    m_bookStore = std::make_shared<BookStore>();
    m_bookStore->setParent(std::shared_ptr<Object>(this));
    m_bookStore->setOrientation(glm::vec3(1, 0, 0));
    m_bookStore->setSize(glm::vec3(2, 1.8, 1.2));
    m_bookStore->setPosition(glm::vec3(0.1, 9, 90));

    m_columns = std::make_shared<Columns>();
    m_columns->setParent(std::shared_ptr<Object>(this));
    m_columns->setPosition(glm::vec3(34, 0, 15));
    m_columns->setSize(glm::vec3(1,1,1.5));

    m_departmentStore = std::make_shared<DepartmentStore>();
    m_departmentStore->setParent(std::shared_ptr<Object>(this));
    m_departmentStore->setPosition(glm::vec3(119.9345, 8, 0.1));
    m_departmentStore->setSize(glm::vec3(1, 2, 1));
    m_departmentStore->setOrientation(glm::vec3(-1, 0, 0));

    m_walls[1]->setOrientation(glm::vec3(-1, 0, 0));
    m_walls[1]->setPosition(glm::vec3(119.9345, 0, 49.9));
    m_walls[1]->setSize(glm::vec3(12, 20,33));

    m_fruitStore = std::make_shared<FruitStore>();
    m_fruitStore->setParent(std::shared_ptr<Object>(this));
    m_fruitStore->setPosition(glm::vec3(119.9345, 8, 59.9));
    m_fruitStore->setSize(glm::vec3(1, 2, 1.5));
    m_fruitStore->setOrientation(glm::vec3(-1, 0, 0));
}

void Mall::update(float dt) {
    m_fruitStore->update(dt);
    m_clothingStore->update(dt);
    m_departmentStore->update(dt);
    m_bookStore->update(dt);
    m_frontWall->update(dt);
}
void Mall::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
    m_storey2->render(mvp, lightPos, lightColor, viewPos);
    m_clothingStore->render(mvp, lightPos, lightColor, viewPos);
    m_bookStore->render(mvp, lightPos, lightColor, viewPos);
    m_columns->render(mvp, lightPos, lightColor, viewPos);
    m_departmentStore->render(mvp, lightPos, lightColor, viewPos);
    m_fruitStore->render(mvp, lightPos, lightColor, viewPos);
    m_frontWall->render(mvp, lightPos, lightColor, viewPos);
    m_walls[0]->render(mvp, lightPos, lightColor, viewPos);
    m_walls[1]->render(mvp, lightPos, lightColor, viewPos);
}
void Mall::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    m_fruitStore->onKeyEvent(key, scancode, action, mode);
    m_clothingStore->onKeyEvent(key, scancode, action, mode);
    m_departmentStore->onKeyEvent(key, scancode, action, mode);
    m_bookStore->onKeyEvent(key, scancode, action, mode);
    m_frontWall->onKeyEvent(key, scancode, action, mode);
    bool pressed = action == GLFW_PRESS;
}
void Mall::onCursorPositionEvent(double x, double y) {}
