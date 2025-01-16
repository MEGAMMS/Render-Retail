#include "Render-Retail/Mall.h"

#include <memory>

#include "GLFW/glfw3.h"
#include "Objects/Object.h"
#include "glm/detail/type_vec.hpp"

Mall::Mall() {
    m_body = std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(this));
    m_body->setPosition(glm::vec3(0));
    m_body->setSize(glm::vec3(80.,20,60));
    // m_body->setOrientation(glm::vec3(0)); 
    m_body->setTexture("assets/brick.png");
    m_body->setFaceTexture(Face::Down,"assets/test-textures/WoodFloor1.png",glm::vec2(2.6, 1) * glm::vec2(2.));
    m_body->setFaceTexture(Face::Up,"assets/test-textures/WoodFloor1.png",glm::vec2(2.6, 1) * glm::vec2(2.));

    m_clothingStore = std::make_shared<ClothingStore>();
    m_clothingStore->setParent(std::shared_ptr<Object>(this));
    m_clothingStore->setPosition(glm::vec3(0.1,9,21));
    m_clothingStore->setSize(glm::vec3(1.5,1.8,1.3));
    m_clothingStore->setOrientation(glm::vec3(1,0,0));

    m_bookStore = std::make_shared<BookStore>();
    m_bookStore->setParent(std::shared_ptr<Object>(this));
    m_bookStore->setOrientation(glm::vec3(1,0,0));
    m_bookStore->setSize(glm::vec3(1.5,1.8,1.));
    m_bookStore->setPosition(glm::vec3(0.1,9,60));

}

void Mall::update(float dt) {}
void Mall::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
    m_clothingStore->render(mvp, lightPos, lightColor, viewPos);
    m_bookStore->render(mvp, lightPos, lightColor, viewPos);
}
void Mall::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
}
void Mall::onCursorPositionEvent(double x, double y) {}
