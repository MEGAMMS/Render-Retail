#include "Challenges/Cubes/Cubes.h"

#include "Application/Application.h"

Cubes::Cubes() {
    camera1 = std::make_shared<Camera>();
    camera2 = std::make_shared<Camera>();
    activeCamera = camera1;
    this->setProjectionMatrixParams(80.0f, 0.001f, 100.0f);

    cube = std::make_shared<Cube>();
}
void Cubes::update(float dt) {
    cube->update(dt);
    activeCamera->update(dt);
    mvp = projection * activeCamera->getViewMatrix();
}

void Cubes::render() {
    cube->render(mvp);
}

void Cubes::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
    activeCamera->onKeyEvent(key, scancode, action, mode);
    if (key == GLFW_KEY_H and pressed) {
        activeCamera = activeCamera == camera1 ? camera2 : camera1;
        activeCamera->resetMousePosition();
    }
}
void Cubes::onCursorPositionEvent(double x, double y) {
    activeCamera->onCursorPositionEvent(x, y);
}