#include "Challenges/RenderRetail/RenderRetail.h"
#include "core.h"
#include "core/Window.h"
#include "AssetManager/AssetManager.h"
#include "Application/Scene.h"

RenderRetail::RenderRetail()
{
    m_camera = std::make_shared<Camera>();

    m_cube = std::make_shared<LightCube>(glm::vec3(1.),glm::vec3(1.));

    glm::vec3 groundPosition(0.f, 0.f, 0.f);  // Position the ground at the origin
    glm::vec2 groundSize(100.f, 100.f);       // Make the ground large (e.g., 100x100 units)
    glm::vec3 groundOrientation(0.f, 1.f, 0.f); // Flat, facing the +Z axis

    m_plains = {
        std::make_shared<Plain>(
        groundPosition,
        groundSize,
        groundOrientation,
            "assets/test-textures/default_pine_wood.png"),
    };

    Mall = std::make_shared<Box>(
            glm::vec3{ 0,6,0 },
            glm::vec3{ 10,5,4},
            glm::vec3{ 0,1,0 },
            std::vector<int>{1,2,4,5,6},
            // glm::vec3{0.3,0.5,0.9}
            "assets/test-textures/default_pine_wood.png"
            );
}
void RenderRetail::update(float dt)
{
    m_cube->update(dt);
    m_camera->update(dt);
    m_VP=projection*m_camera->getViewMatrix();
}

void RenderRetail::render()
{
    m_cube->render(projection*m_camera->getViewMatrix());
    
    for (auto m_plain :m_plains)
        m_plain->render(m_VP,m_cube->getLightPos(),m_cube->getLightColor(),m_camera->getPosition());
    Mall->render(m_VP,m_cube->getLightPos(),m_cube->getLightColor(),m_camera->getPosition());
}

void RenderRetail::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode)
{
    m_camera->onKeyEvent(key,scancode,action,mode);
}

void RenderRetail::onCursorPositionEvent(double x, double y)
{
    m_camera->onCursorPositionEvent(x,y);
}



