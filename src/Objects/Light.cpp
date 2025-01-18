#include "Objects/Light.h"

#include <memory>

#include "AssetManager/AssetManager.h"
#include "Objects/Object.h"
#include "Objects/Sphere.h"
#include "core/Window.h"
#include "glm/detail/type_vec.hpp"

Light::Light(glm::vec3 lightPos, glm::vec3 lightColor) : lightPos(lightPos), lightColor(lightColor) {
    lightShader = AssetManager::instance().loadShaderProgram("LightCube");
    lightShader->activate();
    lightShader->setVec2("u_resolution", Window::instance().getWindowRes());
    m_sphere = std::make_shared<Sphere>(100);
    m_sphere->setParent(std::shared_ptr<Object>(this));
    m_sphere->setPosition(lightPos);
    m_sphere->setSize(glm::vec3(0.5));
    m_sphere->setColor(lightColor);
}

void Light::update(float dt) {}

void Light::render(glm::mat4 mvp) {
    lightShader->activate();
    lightShader->setFloat("u_time", glfwGetTime());
    lightShader->setMat4("mvp", mvp);
    lightShader->setVec3("lightColor", lightColor);
    lightShader->setMat4("model", this->getModel());
    m_sphere->render(mvp, lightPos, lightColor, glm::vec3(0));
}

void Light::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}

void Light::onCursorPositionEvent(double x, double y) {}
