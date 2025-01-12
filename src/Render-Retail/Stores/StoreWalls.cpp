#include "Render-Retail/Stores/StoreWalls.h"


#include <memory>

#include "Objects/Object.h"

StoreWalls::StoreWalls() {
    leftWall = std::make_shared<Box>();
    leftWall->setParent(std::shared_ptr<Object>(this));
    leftWall->setPosition(glm::vec3(4));
    leftWall->setSize(glm::vec3(0.5,0.5,3));
    leftWall->setOrientation(glm::vec3(0.,0.,1.));
    leftWall->setTexture("assets/brick.png");

    rightWall = std::make_shared<Box>();
    rightWall->setParent(std::shared_ptr<Object>(this));
    rightWall->setPosition(glm::vec3(2));
    rightWall->setSize(glm::vec3(0.5,0.5,3));
    rightWall->setOrientation(glm::vec3(0.,0.,1.));
    rightWall->setTexture("assets/brick.png");

    
}

void StoreWalls::update(float dt) {}
void StoreWalls::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    leftWall->render(mvp, lightPos, lightColor, viewPos);
    rightWall->render(mvp, lightPos, lightColor, viewPos);
}
void StoreWalls::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void StoreWalls::onCursorPositionEvent(double x, double y) {}