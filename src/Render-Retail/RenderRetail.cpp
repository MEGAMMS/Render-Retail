#include "Render-Retail/RenderRetail.h"
#include <memory>
#include "Render-Retail/Mall.h"

RenderRetail::RenderRetail() {
    m_camera = std::make_shared<Camera>();
    m_camera->setPosition(glm::vec3(0.));
    m_cube = std::make_shared<LightCube>(glm::vec3(2.), glm::vec3(1.));
    m_mall = std::make_shared<Mall>();
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
    m_mall->render(m_VP,lightPos,lightColor,viewPos);
}

void RenderRetail::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    m_camera->onKeyEvent(key, scancode, action, mode);
}
void RenderRetail::onCursorPositionEvent(double x, double y) { m_camera->onCursorPositionEvent(x, y); }
