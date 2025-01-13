#include "Render-Retail/Objects/Table.h"

#include <memory>

#include "Objects/Object.h"

Table::Table() {
    m_body=std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(this));
    //m_body->setPosition(glm::vec3(5.,0.,7.));
    m_body->setSize(glm::vec3(0.75,0.15,1.));
    //m_body->setOrientation(glm::vec3(1.,0.,0.));
    m_body->setTexture("assets/test-textures/doors_wood.png");
}

void Table::update(float dt) {}
void Table::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
    // for (const auto& leg : m_legs) {
    //             leg->render(mvp, lightPos, lightColor, viewPos);
    //         }
}
void Table::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Table::onCursorPositionEvent(double x, double y) {}