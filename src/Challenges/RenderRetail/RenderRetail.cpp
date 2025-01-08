#include "Challenges/RenderRetail/RenderRetail.h"
#include "core.h"
#include "core/Window.h"
#include "AssetManager/AssetManager.h"
#include "Application/Scene.h"

RenderRetail::RenderRetail()
{
    m_camera = std::make_shared<Camera>();

    m_cube = std::make_shared<LightCube>(glm::vec3(1.),glm::vec3(1.));

    m_plains = {

        std::make_shared<Plain>(
        glm::vec3{ -60,0,60 },
        glm::vec2{ 120,120 },
        glm::vec3{ 0,1,0 },
            "assets/test-textures/dirt_128.png"),

        std::make_shared<Plain>(
        glm::vec3{ -1,0,0 },
        glm::vec2{ 19,1 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plain>(
        glm::vec3{ -1,5,0 },
        glm::vec2{ 19,1 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plain>(
        glm::vec3{ -1,10,0 },
        glm::vec2{ 19,1 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plain>(
        glm::vec3{ -1,1,0 },
        glm::vec2{ 1,9 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plain>(
        glm::vec3{ 10,1,0 },
        glm::vec2{ 1,9 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plain>(
        glm::vec3{ 17,1,0 },
        glm::vec2{ 1,9 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
    };
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
}

void RenderRetail::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode)
{
    m_camera->onKeyEvent(key,scancode,action,mode);
}

void RenderRetail::onCursorPositionEvent(double x, double y)
{
    m_camera->onCursorPositionEvent(x,y);
}



