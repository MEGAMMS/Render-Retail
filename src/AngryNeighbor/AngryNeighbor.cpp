#include "AngryNeighbor/AngryNeighbor.h"
#include "core/Window.h"
#include "Application/Application.h"
#include "AssetManager/AssetManager.h"

AngryNeighbor::AngryNeighbor() {
    camera = std::make_shared<Camera>();
    camera->setPosition(glm::vec3(0, 2, 0));
    ground = std::make_shared<Plane>(
        glm::vec3{ -6,0,6 },
        glm::vec2{ 12,12 },
        glm::vec3{ 0,1,0 },
        glm::vec3{ 0.8,0.9,0.7 }
    );


}
void AngryNeighbor::update(float dt) {
    camera->update(dt);
    mvp = projection * camera->getViewMatrix();
}

void AngryNeighbor::render() {
    ground->render(mvp);
}

void AngryNeighbor::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    camera->onKeyEvent(key, scancode, action, mode);

}
void AngryNeighbor::onCursorPositionEvent(double x, double y) {
    camera->onCursorPositionEvent(x, y);
}