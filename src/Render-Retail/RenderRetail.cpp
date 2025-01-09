#include "Render-Retail/RenderRetail.h"

RenderRetail::RenderRetail() {
    m_camera = std::make_shared<Camera>();
    m_cube = std::make_shared<LightCube>(glm::vec3(2.), glm::vec3(1.));
    m_box = std::make_shared<Box>();
}
void RenderRetail::update(float dt) {
    m_cube->update(dt);
    m_camera->update(dt);
    m_VP = projection * m_camera->getViewMatrix();

    m_box->update(dt);
}

void RenderRetail::render() {
    auto lightPos = m_cube->getLightPos();
    auto lightColor = m_cube->getLightColor();
    auto viewPos = m_camera->getPosition();
    m_cube->render(projection * m_camera->getViewMatrix());
    m_box->render(m_VP, lightPos, lightColor, viewPos);
}

void RenderRetail::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    m_camera->onKeyEvent(key, scancode, action, mode);
}
void RenderRetail::onCursorPositionEvent(double x, double y) { m_camera->onCursorPositionEvent(x, y); }
