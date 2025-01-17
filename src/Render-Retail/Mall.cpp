#include "Render-Retail/Mall.h"

#include <memory>

#include "Objects/Object.h"
#include "glm/detail/type_vec.hpp"

Mall::Mall() {
    m_body = std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(this));
    m_body->setPosition(glm::vec3(0));
    m_body->setSize(glm::vec3(220, 40, 240));
    // m_body->setOrientation(glm::vec3(0));
    m_body->setTexture("assets/brick.png");
    m_body->setFaceTexture(Face::Down, "assets/test-textures/WoodFloor1.png", glm::vec2(2.6, 1) * glm::vec2(2.));
    m_body->setFaceTexture(Face::Up, "assets/test-textures/WoodFloor1.png", glm::vec2(2.6, 1) * glm::vec2(2.));

    m_storey2 = std::make_shared<Box>();
    m_storey2->setParent(std::shared_ptr<Object>(this));
    m_storey2->setPosition(glm::vec3(0, 40, 0));
    m_storey2->setSize(glm::vec3(220, 40, 240));
    // m_storey2->setOrientation(glm::vec3(0));
    m_storey2->setTexture("assets/brick.png");
    m_storey2->setFaceTexture(Face::Down, "assets/test-textures/WoodFloor1.png", glm::vec2(2.6, 1) * glm::vec2(2.));
    m_storey2->setFaceTexture(Face::Up, "assets/test-textures/WoodFloor1.png", glm::vec2(2.6, 1) * glm::vec2(2.));

    m_bookStore = std::make_shared<BookStore>();
    m_bookStore->setParent(std::shared_ptr<Object>(this));
    m_bookStore->setOrientation(glm::vec3(-1, 0, 0));
    m_bookStore->setSize(glm::vec3(4.2, 3.3, 5));
    m_bookStore->setPosition(glm::vec3(219.7, 18, 130));

    m_fruitStore = std::make_shared<FruitStore>();
    m_fruitStore->setParent(std::shared_ptr<Object>(this));
    m_fruitStore->setOrientation(glm::vec3(-1, 0, 0));
    m_fruitStore->setSize(glm::vec3(4.2, 2.8, 4));
    m_fruitStore->setPosition(glm::vec3(219.7, 18, 0.2));

    m_columns = std::make_shared<Columns>();
    m_columns->setParent(std::shared_ptr<Object>(this));
    m_columns->setSize(glm::vec3(2));
    m_columns->setPosition(glm::vec3(68, 0, 22));

    m_departmentStore = std::make_shared<DepartmentStore>();
    m_departmentStore->setParent(std::shared_ptr<Object>(this));
    m_departmentStore->setOrientation(glm::vec3(1, 0, 0));
    m_departmentStore->setSize(glm::vec3(3, 3.6, 3.2));
    m_departmentStore->setPosition(glm::vec3(0.2, 16, 226));

    m_clothingStore = std::make_shared<ClothingStore>();
    m_clothingStore->setParent(std::shared_ptr<Object>(this));
    m_clothingStore->setOrientation(glm::vec3(1, 0, 0));
    m_clothingStore->setSize(glm::vec3(4, 3.6, 7));
    m_clothingStore->setPosition(glm::vec3(0.2, 18, 75));
}

void Mall::update(float dt) {
    m_fruitStore->update(dt);
    m_clothingStore->update(dt);
    m_departmentStore->update(dt);
    m_bookStore->update(dt);
}
void Mall::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
    m_storey2->render(mvp, lightPos, lightColor, viewPos);
    m_clothingStore->render(mvp, lightPos, lightColor, viewPos);
    m_bookStore->render(mvp, lightPos, lightColor, viewPos);
    m_columns->render(mvp, lightPos, lightColor, viewPos);
    m_departmentStore->render(mvp, lightPos, lightColor, viewPos);
    m_fruitStore->render(mvp, lightPos, lightColor, viewPos);
}
void Mall::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    m_fruitStore->onKeyEvent(key, scancode, action, mode);
    m_clothingStore->onKeyEvent(key, scancode, action, mode);
    m_departmentStore->onKeyEvent(key, scancode, action, mode);
    m_bookStore->onKeyEvent(key, scancode, action, mode);
    bool pressed = action == GLFW_PRESS;
}
void Mall::onCursorPositionEvent(double x, double y) {}
