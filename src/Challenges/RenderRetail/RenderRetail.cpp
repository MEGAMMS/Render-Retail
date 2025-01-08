#include "Challenges/RenderRetail/RenderRetail.h"
#include "core.h"
#include "core/Window.h"
#include "AssetManager/AssetManager.h"
#include "Application/Scene.h"

RenderRetail::RenderRetail()
{
    m_camera = std::make_shared<Camera>();

    m_cube = std::make_shared<LightCube>(glm::vec3(1.),glm::vec3(1.));

    m_plain;
}
void RenderRetail::update(float dt)
{
    m_cube->update(dt);
    m_camera->update(dt);
}

void RenderRetail::render()
{
    m_cube->render(projection*m_camera->getViewMatrix());
}

void RenderRetail::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode)
{
    m_camera->onKeyEvent(key,scancode,action,mode);
}

void RenderRetail::onCursorPositionEvent(double x, double y)
{
    m_camera->onCursorPositionEvent(x,y);
}



