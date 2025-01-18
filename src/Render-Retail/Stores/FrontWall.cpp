#include "Render-Retail/Stores/FrontWall.h"

#include <memory>

#include "Objects/Object.h"

FrontWall::FrontWall() {
    for (int i = 0; i < 3; ++i) {
        frontWall.push_back(std::make_shared<Box>());
    }

    m_door = std::make_shared<Door>();
    m_door->setParent(std::shared_ptr<Object>(this));
    m_door->setTexture("assets/textures/Cottage-Double-Slider.png");
    m_door->setPosition(glm::vec3(2.5f, -10 / 2, 0.0f));
    m_door->setSize(glm::vec3(5.f, 5.1, 1.f));
    m_door->setOrientation(glm::vec3(0.,0,1));

    frontWall[0]->setPosition(glm::vec3(0.0f, -10 / 2, 0.0f));
    frontWall[0]->setSize(glm::vec3(2.5f, 11., 1.f));

    frontWall[1]->setPosition(glm::vec3(7.3f, -10 / 2, 0.0f));
    frontWall[1]->setSize(glm::vec3(2.7f, 11., 1.f));

    frontWall[2]->setPosition(glm::vec3(2.50f, 3.5, 0.0f));
    frontWall[2]->setSize(glm::vec3(4.9,2.5, 1.f));

    for (int i = 0; i < 3; ++i) {
        frontWall[i]->setTexture("assets/brick.png");
        frontWall[i]->setParent(std::shared_ptr<Object>(this));
    }
}

void FrontWall::update(float dt) {
    m_door->update(dt);
}
void FrontWall::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    for (const auto& part : frontWall) {
        part->render(mvp, lightPos, lightColor, viewPos);
    }
    m_door->render(mvp, lightPos, lightColor, viewPos);
}
void FrontWall::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    m_door->onKeyEvent(key,scancode,action,mode);
    bool pressed = action == GLFW_PRESS;
}
void FrontWall::onCursorPositionEvent(double x, double y) {}


void FrontWall::setTexture(const std::string& texturePath) {
    for (const auto& wall : frontWall) {
        wall->setTexture(texturePath);
    }
}