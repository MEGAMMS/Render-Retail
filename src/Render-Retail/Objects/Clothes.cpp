#include "Render-Retail/Objects/Clothes.h"

#include <memory>

#include "Objects/Object.h"

Clothes::Clothes(unsigned int shirts) {
    m_hanger = std::make_shared<Hanger>();
    m_hanger->setParent(std::shared_ptr<Object>(this));
    m_hanger->setPosition(glm::vec3(0,0,0));
    m_hanger->setSize(glm::vec3(0.3));

    float space = 1. / (shirts);
    for (int i = 0; i < shirts; i++) {
        auto shirt= std::make_shared<Shirt>();
        shirt->setParent(std::shared_ptr<Object>(this));
        shirt->setSize(glm::vec3(1));
        shirt->setPosition(glm::vec3(-0.3,-0.55,1-(space*(i+1)*2)));
        m_shirts.push_back(shirt);
    }
}

void Clothes::update(float dt) {}
void Clothes::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_hanger->render(mvp, lightPos, lightColor, viewPos);
    for (const auto& shirt : m_shirts) {
        shirt->render(mvp, lightPos, lightColor, viewPos);
    }
}
void Clothes::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Clothes::onCursorPositionEvent(double x, double y) {}