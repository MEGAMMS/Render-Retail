#pragma once

#include "core.h"
#include "core/Window.h"

class Scene {
public:
    glm::mat4 projection;
    virtual ~Scene() = default;
    Scene() {
        updateProjectionMatrix();
    }
    // Virtual methods to be implemented by each scene
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
    virtual void onCursorPositionEvent(double x, double y) {}
    void onResized() {
        updateProjectionMatrix();
    };
    void setProjectionMatrixParams(float fov, float nearPlane, float farPlane) {
        this->fov = fov;
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;
        updateProjectionMatrix();
    }
private:
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    void updateProjectionMatrix() {
        float aspect = Window::instance().getWindowAspectRatio();
        projection = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
    }
};
