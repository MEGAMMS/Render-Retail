#pragma once

#include "core.h"
#include "Application/scene.h"
#include "core/Camera.h"
#include "AngryNeighbor/Plane.h"
#include "AngryNeighbor/Box.h"
#include "AngryNeighbor/Door.h"

class AngryNeighbor : public Scene {
private:
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<Plane>> planes;
    std::vector<std::shared_ptr<Box>> boxes;
    std::vector<std::shared_ptr<Door>> doors;

    glm::mat4 mvp = glm::mat4(1.f);
public:
    AngryNeighbor();
    void update(float dt) override;
    void render() override;

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;
};