#include "Render-Retail/RenderRetail.h"

#include <memory>

#include "Objects/Cone.h"
#include "Render-Retail/Mall.h"
#include "Render-Retail/Objects/Door.h"
#include "glm/detail/type_vec.hpp"

RenderRetail::RenderRetail() {
    m_camera = std::make_shared<Camera>();
    m_camera->setPosition(glm::vec3(12.3597, 2.82287, 35.3499));

    m_cube = std::make_shared<LightCube>(glm::vec3(9.04054, 8.12076, 6.62954), glm::vec3(1.));

    m_mall = std::make_shared<Mall>();
    m_mall->setSize(glm::vec3(0.2));

    m_rock = std::make_shared<Model>("assets/objects/rock/rock.obj");

    m_plane = std::make_shared<Model>("assets/objects/chêne/tree 1.obj");
    m_plane->setSize(glm::vec3(0.13));
    m_plane->setOrientation(glm::vec3(0, 1, 0));
    m_plane->setPosition(glm::vec3(0));

    m_grass = std::make_shared<Box>();
    m_grass->setSize(glm::vec3(40,0.2,44));
    m_grass->setOrientation(glm::vec3(1, 0, 0));
    m_grass->setPosition(glm::vec3(-1.9123,-0.211544,21.7459));
    m_grass->setTexture("assets/test-textures/Grass001.png");

    m_street = std::make_shared<Box>();
    m_street->setSize(glm::vec3(3,0.2,44));
    m_street->setOrientation(glm::vec3(1, 0, 0));
    m_street->setPosition(glm::vec3(-1.9123,-.184925,17.4586));
    m_street->setTexture("assets/test-textures/Road007.png");

    m_elevator = std::make_shared<Elevator>();
    m_door = std::make_shared<Door>();
    m_elevator->setPosition(glm::vec3(170, 0, 1));
}
void RenderRetail::update(float dt) {
    m_cube->update(dt);
    m_camera->update(dt);
    std::cout << m_camera->getPosition().x << "," << m_camera->getPosition().y << "," << m_camera->getPosition().z
              << std::endl;
    m_VP = projection * m_camera->getViewMatrix();
    m_elevator->update(dt);
    m_door->update(dt);
    m_mall->update(dt);
}

void RenderRetail::render() {
    auto lightPos = m_cube->getLightPos();
    auto lightColor = m_cube->getLightColor();
    auto viewPos = m_camera->getPosition();
    m_cube->render(projection * m_camera->getViewMatrix());

    m_mall->render(m_VP, lightPos, lightColor, viewPos);
    // m_plane->render(m_VP, lightPos, lightColor, viewPos);
    m_street->render(m_VP, lightPos, lightColor, viewPos);
    m_grass->render(m_VP, lightPos, lightColor, viewPos);
    // m_rock->render(m_VP, lightPos, lightColor, viewPos);
    // m_cone->render(m_VP, lightPos, lightColor, viewPos);
    // m_sphere->render(m_VP, lightPos, lightColor, viewPos);
    m_elevator->render(m_VP, lightPos, lightColor, viewPos);
    m_door->render(m_VP, lightPos, lightColor, viewPos);
}

void RenderRetail::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    m_camera->onKeyEvent(key, scancode, action, mode);
    m_mall->onKeyEvent(key, scancode, action, mode);
    m_elevator->onKeyEvent(key, scancode, action, mode);
    m_door->onKeyEvent(key, scancode, action, mode);
    bool pressed = action == GLFW_PRESS;
}
void RenderRetail::onCursorPositionEvent(double x, double y) { m_camera->onCursorPositionEvent(x, y); }
