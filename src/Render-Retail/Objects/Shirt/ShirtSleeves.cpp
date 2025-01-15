#include "Render-Retail/Objects/Shirt/ShirtSleeves.h"

#include <memory>

#include "Objects/Object.h"

ShirtSleeves::ShirtSleeves() {

    for (int i = 0; i < 2; i++) {
        m_sleeves.push_back(std::make_shared<Cone>(0.5, 0.1, 0.1, 100));
    }

    for (int i = 0; i < 2; i++) {
        m_sleeves[i]->setParent(std::shared_ptr<Object>(this));
        m_sleeves[i]->setColor(glm::vec3(1., 0., 0.));
        m_sleeves[i]->setSize(glm::vec3(1));
    }

    m_sleeves[0]->setPosition(glm::vec3(-0.3, 0.1, 0));
    m_sleeves[0]->setOrientation(glm::vec3(0.5, 1.0, 0.));
    m_sleeves[0]->setBaseVisibility(0,1);

    m_sleeves[1]->setPosition(glm::vec3(0.3, 0.1, 0));
    m_sleeves[1]->setOrientation(glm::vec3(-0.5, 1.0, 0.));
    m_sleeves[1]->setBaseVisibility(0,1);
}

void ShirtSleeves::update(float dt) {}
void ShirtSleeves::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    for (const auto& sleeve : m_sleeves) {
        sleeve->render(mvp, lightPos, lightColor, viewPos);
    }
}
void ShirtSleeves::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void ShirtSleeves::onCursorPositionEvent(double x, double y) {}