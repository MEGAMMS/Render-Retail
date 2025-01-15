#include "Render-Retail/RenderRetail.h"

#include <memory>

#include "Objects/Cone.h"
#include "Render-Retail/Mall.h"
#include "glm/detail/type_vec.hpp"

RenderRetail::RenderRetail() {
    m_camera = std::make_shared<Camera>();
    m_camera->setPosition(glm::vec3(0.));
    m_cube = std::make_shared<LightCube>(glm::vec3(2.), glm::vec3(1.));
    m_mall = std::make_shared<Mall>();
    m_cone = std::make_shared<Cone>(2, 1, 1, 100);
    m_cone->setTexture("assets/test-textures/Wood1.png", "");
    m_cone->setSize(glm::vec3(0.3, 0.1, 0.5));
}
void RenderRetail::update(float dt) {
    m_cube->update(dt);
    m_camera->update(dt);
    m_VP = projection * m_camera->getViewMatrix();

    m_mall->update(dt);
    m_mall->setSize(glm::vec3(0.1));
}

void RenderRetail::render() {
    auto lightPos = m_cube->getLightPos();
    auto lightColor = m_cube->getLightColor();
    auto viewPos = m_camera->getPosition();
    m_cube->render(projection * m_camera->getViewMatrix());
    m_mall->render(m_VP, lightPos, lightColor, viewPos);
    // m_cone->render(m_VP, lightPos, lightColor, viewPos);
}

void RenderRetail::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    m_camera->onKeyEvent(key, scancode, action, mode);
}
void RenderRetail::onCursorPositionEvent(double x, double y) { m_camera->onCursorPositionEvent(x, y); }
