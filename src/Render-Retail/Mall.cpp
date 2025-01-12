#include "Render-Retail/Mall.h"

#include <memory>

#include "Objects/Object.h"

Mall::Mall() {
    m_box = std::make_shared<Box>();
    m_box->setParent(std::shared_ptr<Object>(this));
    m_box->setPosition(glm::vec3(0));
    m_box->setSize(glm::vec3(5.));
    // m_box->setOrientation(glm::vec3(-1.));
    // m_box->setTexture("assets/brick.png");
    m_box->setFaceTexture(Face::Front, "assets/brick.png");
    m_box->setFaceVisibility(Face::Right, false);
    
    m_clothingStore=std::make_shared<ClothingStore>(); 
    m_clothingStore->setParent(std::shared_ptr<Object>(this));

}

void Mall::update(float dt) {}
void Mall::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_box->render(mvp, lightPos, lightColor, viewPos);
    m_clothingStore->render(mvp,lightPos,lightColor,viewPos);
}
void Mall::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Mall::onCursorPositionEvent(double x, double y) {}
