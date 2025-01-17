#include "Render-Retail/Objects/Columns.h"

#include <memory>

#include "Objects/Object.h"

Columns::Columns() {
    
    for (int i = 0; i <4; i++) {
        auto m_Column = std::make_shared<Box>();
        m_Column->setParent(std::shared_ptr<Object>(this));
        m_Column->setOrientation(glm::vec3(0., 0., 1));
        m_Column->setSize(glm::vec3(5, 20, 5));
        m_Column->setTexture("assets/test-textures/WoodFloor1.png");
        m_Columns.push_back(m_Column);
    }
    float space=32;
      m_Columns[0]->setPosition(glm::vec3(0, 0, 0));
      m_Columns[1]->setPosition(glm::vec3(space, 0, 0));
      m_Columns[2]->setPosition(glm::vec3(0, 0, space));
      m_Columns[3]->setPosition(glm::vec3(space, 0, space));
}

void Columns::update(float dt) {}
void Columns::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    for (const auto& Column : m_Columns) {
        Column->render(mvp, lightPos, lightColor, viewPos);
    }
}
void Columns::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Columns::onCursorPositionEvent(double x, double y) {}