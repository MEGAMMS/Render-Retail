#include "Render-Retail/Objects/Shirt.h"

#include <memory>

#include "Objects/Object.h"

Shirt::Shirt() {
    m_body = std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(this));
    m_body->setPosition(glm::vec3(0));
    m_body->setSize(glm::vec3(0.5, 0.5, 0.1));
    m_body->setTexture("assets/test-textures/red_shirt.png");

    for (int i = 0; i < 2; i++) {
        m_sleeves.push_back(std::make_shared<Cone>(0.5, 0.1, 0.1, 100));
    }

    for (int i = 0; i < 2; i++) {
        m_sleeves[i]->setParent(std::shared_ptr<Object>(this));
        m_sleeves[i]->setColor(glm::vec3(1., 0., 0.));
        m_sleeves[i]->setSize(glm::vec3(1));
    }

    m_sleeves[0]->setPosition(glm::vec3(-0.3, 0.1, 0));
    m_sleeves[0]->setOrientation(glm::vec3(0.0, 0.0, -30.0f));

    m_sleeves[1]->setPosition(glm::vec3(0.3, 0.1, 0));
    m_sleeves[1]->setOrientation(glm::vec3(0.0, 0.0, 30.0f));
}

void Shirt::update(float dt) {}
void Shirt::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
    for (const auto& sleeve : m_sleeves) {
        sleeve->render(mvp, lightPos, lightColor, viewPos);
    }
}
void Shirt::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Shirt::onCursorPositionEvent(double x, double y) {}