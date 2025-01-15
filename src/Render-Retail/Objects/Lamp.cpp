#include "Render-Retail/Objects/Lamp.h"

#include <memory>

#include "Objects/Object.h"

Lamp::Lamp() {
    m_cable = std::make_shared<Cone>(3, 0.03, 0.03, 200);
    m_cable->setParent(std::shared_ptr<Object>(this));
    m_cable->setPosition(glm::vec3(0));
    m_cable->setSize(glm::vec3(1));
    m_cable->setOrientation(glm::vec3(0., 1., 0.));
    m_cable->setColor(glm::vec3(0.69, 0.52, 0.1));

    m_cover = std::make_shared<Cone>(1, 0.04, 1.5, 100);
    m_cover->setParent(std::shared_ptr<Object>(this));
    m_cover->setPosition(glm::vec3(0, -1.5, 0));
    m_cover->setSize(glm::vec3(1));
    m_cover->setOrientation(glm::vec3(0., 1., 0.));
    m_cover->setColor(glm::vec3(0.69, 0.62, 0.30));
    m_cover->setBaseVisibility(0, 0);

    m_bulb = std::make_shared<Sphere>(100);
    m_bulb->setParent(std::shared_ptr<Object>(this));
    m_bulb->setPosition(glm::vec3(0, -1.8, 0));
    m_bulb->setSize(glm::vec3(0.3));
    m_bulb->setColor(glm::vec3(1., 1., 0.));
}

void Lamp::update(float dt) {}
void Lamp::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_cable->render(mvp, lightPos, lightColor, viewPos);
    m_cover->render(mvp, lightPos, lightColor, viewPos);
    m_bulb->render(mvp, lightPos, lightColor, viewPos);
}
void Lamp::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Lamp::onCursorPositionEvent(double x, double y) {}

void Lamp::setBulbColor(glm::vec3 color) { m_bulb->setColor(color); }

void Lamp::setCableColor(glm::vec3 color) { m_cable->setColor(color); }

void Lamp::setCoverColor(glm::vec3 color) { m_cover->setColor(color); }