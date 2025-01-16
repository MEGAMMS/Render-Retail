#include "Render-Retail/Objects/TableLegs.h"

#include <memory>

#include "Objects/Object.h"

TableLegs::TableLegs() {
    for (int i = 0; i < 4; ++i) {
        m_legs.push_back(std::make_shared<Box>());
    }

    float legHeight = 0.85f;  // Height of the legs
    float legSize = 0.1f;     // Thickness of the legs

    // Position the legs
    m_legs[0]->setPosition(glm::vec3(0, 0, 0));
    m_legs[1]->setPosition(glm::vec3(0., 0, 0.9));
    m_legs[2]->setPosition(glm::vec3(0.74, 0, 0));
    m_legs[3]->setPosition(glm::vec3(0.74, 0, 0.9));

    // Set leg sizes and textures
    for (auto& leg : m_legs) {
        leg->setSize(glm::vec3(legSize, legHeight, legSize));
        leg->setParent(std::shared_ptr<Object>(this));
        leg->setTexture("assets/test-textures/Wood1.png");
    }
}

void TableLegs::update(float dt) {}
void TableLegs::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    for (const auto& leg : m_legs) {
        leg->render(mvp, lightPos, lightColor, viewPos);
    }
}
void TableLegs::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void TableLegs::onCursorPositionEvent(double x, double y) {}

void TableLegs::setTexture(const std::string& texturePath)
{
   for (const auto& leg : m_legs) {
        leg->setTexture(texturePath);
    }
}
