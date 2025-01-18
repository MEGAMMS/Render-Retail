#include "Render-Retail/RenderRetail.h"

#include <memory>

#include "Objects/Cone.h"
#include "Objects/Light.h"
#include "Render-Retail/Mall.h"
#include "Render-Retail/Objects/Door.h"
#include "Render-Retail/Objects/MoonAndSun.h"
#include "glm/detail/type_vec.hpp"

#include "External/include/Globals.hpp"
#include "External/include/Textures.hpp"
#include "External/include/Scene.hpp"

RenderRetail::RenderRetail() {
// Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_camera = std::make_shared<Camera>();
    m_camera->setPosition(glm::vec3(12.3597, 2.82287, 35.3499));

    m_light = std::make_shared<Light>(glm::vec3(100), glm::vec3(1));
    moonAndSun = std::make_shared<MoonAndSun>(50.0f, glm::vec3(0.8f, 0.3f, 0.0f), 30.0f);

    m_mall = std::make_shared<Mall>();
    m_mall->setSize(glm::vec3(0.2));
    m_mall->setPosition(glm::vec3(10.4907,0,0.0313));

    for (int i = 0; i < 10; i++) {
        auto tree = std::make_shared<::Model>("assets/objects/fur_tree/scene.gltf");
        tree->setPosition(glm::vec3(6.65025,0.,21.9676-(i*3)));
        tree->setOrientation(glm::vec3(1, 0, 0));
        tree->setSize(glm::vec3(0.01));

        m_trees.push_back(tree);
    }

    for (int i = 0; i < 10; i++) {
        auto tree = std::make_shared<::Model>("assets/objects/fur_tree/scene.gltf");
        tree->setPosition(glm::vec3(37.9363,0.,21.9676-(i*3)));
        tree->setOrientation(glm::vec3(1, 0, 0));
        tree->setSize(glm::vec3(0.01));

        m_trees.push_back(tree);
    }


    m_plane = std::make_shared<::Model>("assets/objects/chêne/tree 1.obj");
    m_plane->setSize(glm::vec3(0.13));
    m_plane->setOrientation(glm::vec3(0, 1, 0));
    m_plane->setPosition(glm::vec3(0));

    m_grass = std::make_shared<Box>();
    m_grass->setSize(glm::vec3(50,0.2,44));
    m_grass->setOrientation(glm::vec3(1, 0, 0));
    m_grass->setPosition(glm::vec3(-1.9123, -0.211544, 26.7459));
    m_grass->setTexture("assets/test-textures/Grass001.png");

    m_street = std::make_shared<Box>();
    m_street->setSize(glm::vec3(3, 0.2, 44));
    m_street->setOrientation(glm::vec3(1, 0, 0));
    m_street->setPosition(glm::vec3(-1.9123,-.184925,26.4586));
    m_street->setTexture("assets/test-textures/Road007.png");
    
    m_door = std::make_shared<Door>();


    workspace::Shaders::compile();
    workspace::Textures::load();
    workspace::Scene::prepare();
}
void RenderRetail::update(float dt) {
    m_light->update(dt);
    m_camera->update(dt);
    std::cout << m_camera->getPosition().x << "," << m_camera->getPosition().y << "," << m_camera->getPosition().z
              << std::endl;
    m_VP = projection * m_camera->getViewMatrix();
    m_door->update(dt);
    m_mall->update(dt);
    moonAndSun->update(dt);
}

void RenderRetail::render() {
    auto lightPos = m_light->getLightPos();
    auto lightColor = m_light->getLightColor();
    auto viewPos = m_camera->getPosition();
    m_light->render(projection * m_camera->getViewMatrix());
    lightPos = moonAndSun->getLightPos();
    lightColor = moonAndSun->getLightColor();
    viewPos = m_camera->getPosition();
    moonAndSun->render(m_VP);

    m_mall->render(m_VP, lightPos, lightColor, viewPos);

    m_street->render(m_VP, lightPos, lightColor, viewPos);
    m_grass->render(m_VP, lightPos, lightColor, viewPos);

    
    for (const auto& tree : m_trees) {
        tree->render(m_VP, lightPos, lightColor, viewPos);
    }

    workspace::Scene::draw(mat4(1),m_camera->getViewMatrix(),projection,m_camera->getPosition());
    m_light->render(m_VP);
    // m_rock->render(m_VP, lightPos, lightColor, viewPos);
    // m_cone->render(m_VP, lightPos, lightColor, viewPos);
    // m_sphere->render(m_VP, lightPos, lightColor, viewPos);
    // m_elevator->render(m_VP, lightPos, lightColor, viewPos);
    // m_door->render(m_VP, lightPos, lightColor, viewPos);
}

void RenderRetail::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    m_camera->onKeyEvent(key, scancode, action, mode);
    m_mall->onKeyEvent(key, scancode, action, mode);
    m_door->onKeyEvent(key, scancode, action, mode);
    moonAndSun->onKeyEvent(key, scancode, action, mode);
    bool pressed = action == GLFW_PRESS;
}
void RenderRetail::onCursorPositionEvent(double x, double y) { m_camera->onCursorPositionEvent(x, y); }
